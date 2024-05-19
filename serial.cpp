//-------------------------------------------
// serial.cpp
//-------------------------------------------
// initial implementation not at all like
// the final one.  We merely display whatever
// comes from the TE3_hub as debugging output,
// and have a custom built test processor to
// handle text Serial input to the TE3, parse
// it on a line by line basis, and send Serial
// MIDI Messages to the TE3_hub.
//
// For telnet, accepts STA_SSID= and STA_PASS=
// commands over the USB Serial port, and attempts
// to connect to Wifi.  If it works, the values
// are stored in EEPROM.


#include "serial.h"
#include <myDebug.h>
#include <teSGTL5000.h>
#include <teMIDI.h>


#define dbg_cmd  0
#define dbg_telnet 0


#define MAX_STRING  255

#define USB_SERIAL_PORT     Serial


#ifdef ESP32

    #define WITH_TELNET     1

    #include <HardwareSerial.h>
    #include <nvs_flash.h>
    #include <Preferences.h>
    #include "WiFi.h"
    // #include <driver/uart.h>

    #if WITH_TELNET
        #include <ESPTelnetStream.h>
    #endif

    #define HUB_SERIAL_RX   27
    #define HUB_SERIAL_TX   26

    #define WIFI_CONNECT_TIMEOUT        10000
    #define WIFI_DISCONNECT_TIMEOUT     10000

    Preferences preferences;

    HardwareSerial HUB_SERIAL_PORT(1);

#else

    #define HUB_SERIAL_PORT Serial1

#endif


static void processCommandLine(const char *line);
    // forward


//-----------------------------------------
// telnet
//-----------------------------------------

#if defined(ESP32) && WITH_TELNET

    #define MAX_TELNET_STRINGS   1000

    volatile int telnet_head = 0;
    volatile int telnet_tail = 0;
    String telnet_queue[MAX_TELNET_STRINGS];
    static bool telnet_started = false;
    static bool telnet_connected = false;

    ESPTelnetStream telnet;


    void onTelnetConnect(String ip)
    {
        telnet_connected = true;
        extraSerial = &telnet; // in myDebug.h
        display(dbg_telnet,"TE3 telnet connected from %s",ip.c_str());
    }

    void onTelnetDisconnect(String ip)
    {
        telnet_connected = false;
        extraSerial = NULL; // in myDebug.h
        display(dbg_telnet,"Telnet %s disconnected",ip.c_str());
    }

    void onTelnetReconnect(String ip)
    {
        telnet_connected = true;
        extraSerial = &telnet; // in myDebug.h
        display(dbg_telnet,"Telnet reconnected from %s",ip.c_str());
    }

    void onTelnetConnectionAttempt(String ip)
    {
        display(dbg_telnet,"Telnet %s tried to connect",ip.c_str());
    }

    // void onTelnetReceived(String command)
    // {
    //     display(dbg_telnet,"Telnet Received(%d): '%s'",command.length(),command.c_str());
    //     processCommandLine(command.c_str());
    // }

    void enqueTelnet(const char *line)
    {
        // display(0,"enqueueTelenet(%d,%d)=%s",telnet_head,telnet_tail,line);

        int new_head = telnet_head;
        if (new_head + 1 >= MAX_TELNET_STRINGS)
            new_head = 0;
        else
            new_head++;
        if (new_head == telnet_tail)
        {
            my_error("telnet_out_buffer overflow",0);
        }
        else
        {
            telnet_queue[telnet_head] = line;
            telnet_head = new_head;
        }
    }

    void dequeueTelnet()
    {
        while (telnet_tail != telnet_head)
        {
            if (!telnet_started || !telnet_connected)
            {
                telnet_tail = telnet_head;
                return;
            }

            // display(0,"dequeueTelenet(%d,%d)=%s",telnet_head,telnet_tail,telnet_queue[telnet_tail].c_str());

            telnet.println(telnet_queue[telnet_tail].c_str());
            telnet_tail++;
            if (telnet_tail >= MAX_TELNET_STRINGS)
                telnet_tail = 0;
        }
    }


    void telnetTask(void *param)
    {
        delay(1000);
        display(dbg_telnet,"starting telnetTask loop on core(%d)",xPortGetCoreID());
        delay(1000);
        while (1)
        {
            vTaskDelay(1);  // 1ms
            dequeueTelnet();
        }
    }


    void init_telnet()
    {
        telnet.onConnect(onTelnetConnect);
        telnet.onConnectionAttempt(onTelnetConnectionAttempt);
        telnet.onReconnect(onTelnetReconnect);
        telnet.onDisconnect(onTelnetDisconnect);
        // telnet.onInputReceived(onTelnetReceived);

        // runs on ESP32_CORE_ARDUINO==1
        // otherwise run on ESP32_CORE_OTHER==0
        // see notes in bilgeAlarm.cpp lcdPrint()
        display(dbg_telnet,"starting telnetTask pinned to core %d",1);
        xTaskCreatePinnedToCore(
            telnetTask,
            "telnetTask",
            8000,
            NULL,
            1,  	// priority
            NULL,   // handle
            1);     // ESP32_CORE_ARDUINO
    }


#endif  // ESP32 && WITH_TELNET


//===================================
// ESP32 WIFI
//===================================

#ifdef ESP32

    static void connectWifi(const String &ssid, const String &pass)
    {
        display(0,"TE3 serial.cpp connectWiFi() started",0);
        proc_entry();

        wifi_mode_t mode = WiFi.getMode();
        if (mode != WIFI_AP_STA)
        {
            WiFi.mode(WIFI_STA);
            delay(400);
        }

        #if WITH_TELNET
            if (telnet_started)
            {
                display(0,"telnet stopped",0);
                telnet.stop();
                telnet_started = false;
            }
        #endif
        if (WiFi.status() == WL_CONNECTED)
        {
            WiFi.disconnect();
            display(0,"disconnecting station ...",0);
            uint32_t start = millis();
            while (WiFi.status() == WL_CONNECTED)
            {
                if (millis() > start + WIFI_DISCONNECT_TIMEOUT)
                {
                    my_error("could not discconnect station!!",0);
                    break;
                }
                delay(500);
            }
        }

        if (ssid != "" && pass != "")
        {
            display(0,"Connecting to (%s:%s)",ssid.c_str(),pass.c_str());

            bool timeout = false;
            uint32_t start = millis();
            WiFi.begin(ssid.c_str(),pass.c_str());

            // delay(400);

            while (WiFi.status() != WL_CONNECTED)
            {
                delay(500);
                if (millis() > start + WIFI_CONNECT_TIMEOUT)
                {
                    timeout = true;
                    break;
                }
            }

            if (timeout)
            {
                my_error("Could not connect to %s",ssid.c_str());
            }
            else
            {
                String ip = WiFi.localIP().toString();
                warning(0,"Connected to %s at IP=%s",ssid.c_str(),ip.c_str());

                #if WITH_TELNET
                    telnet.begin();
                    telnet_started = true;
                    display(0,"telnet started",0);
                #endif
            }
        }

        proc_leave();
        display(0,"connect() finished",0);
    }

#endif




//---------------------------------------------
// initSerial
//---------------------------------------------


void init_serial()
{
    // delay(1000);
    // setColorString(COLOR_CONST_DEFAULT, "\033[94m");  // example for bright blue
        // TE3's normal (default) display color is green
        // TE3_hubs normal display color is bright blue
        // Looper's normal display color, is cyan, I think

    #ifdef ESP32
        // switching ESP32 to 921600 baud.
        // 921600 is the fast ESP32 upload speed.
        // If I use it, and Serial.begin(115200), I have to unplug
        //      and replug the ESP32 in to get it to work.
        // In fact the problem does not appear to be the ESP32,
        //      but the attached cp210x chip and/or Win10 cp210x
        //      driver.
        // I *think* that what happens is that no matter what I do,
        //      after a fast upload, the cp210x chip is left at 921600,
        //      and there is no apparent way to get it reset to the
        //      ESP32 uart0 baud rate.
        // I made a test mod to the console.pm program and it can
        //      detect when it opens a serial port at a given
        //      baud rate but the actual baud rate is not what
        //      is specified in the Win32::SerialPort setup.
        // So the problem happens on both sides, and appears
        //      to be the fault of this cp210x approach on
        //      both sides.

        Serial.begin(921600);

    #else
        Serial.begin(115200);
    #endif

    delay(200);
    // dbgSerial = &Serial;
    display(0,"TE3 init_serial()",0);

    #ifdef ESP32

        preferences.begin("TE3", false);
    
        HUB_SERIAL_PORT.begin(115200, SERIAL_8N1, HUB_SERIAL_RX, HUB_SERIAL_TX);

        #if WITH_TELNET
            init_telnet();
        #endif

        String ssid = preferences.getString("STA_SSID", "");
        String pass = preferences.getString("STA_PASS", "");
        if (ssid != "" && pass != "")
            connectWifi(ssid,pass);

    #else
        HUB_SERIAL_PORT.begin(115200);
    #endif

    delay(200);
}


//---------------------------------------------
// command atoms
//---------------------------------------------

static void reboot()
{
    warning(0,"REBOOTING TE3!!",0);
    delay(300);
    #ifdef ESP32
        ESP.restart();
    #endif
}

static void reset()
{
    warning(0,"RESETTING TE3!!",0);
    delay(300);
    #ifdef ESP32
        nvs_flash_erase(); // erase the NVS partition and...
        nvs_flash_init(); // initialize the NVS partition.
    #endif
    reboot();
}



//---------------------------------------------
// command processor
//---------------------------------------------


static bool StringEqI(const String &s1, const char *s2)
{
    return !strcasecmp(s1.c_str(),s2);
}


static bool validInt(uint8_t *rslt, const String &left, const String right, uint8_t max)
{
    int val = 0;
    for (int i=0; i<right.length(); i++)
    {
        char c = right[i];
        if (c < '0' || c > '9')
        {
            my_error("command(%s)=%s invalid integer",left.c_str(),right.c_str());
            return false;
        }
        val = val * 10 + (c - '0');
    }
    if (val > max)
    {
        my_error("command(%s)=%s out_of_range(%d)",left.c_str(),right.c_str(),max);
        return false;
    }

    *rslt = val;
    return true;
}



static void handleCommand(const String &left, const String &right)
{
    display(dbg_cmd,"handleCommand(%s)=%s",left.c_str(),right.c_str());

    // MONADIC COMMANDS

    if (StringEqI(left,"REBOOT"))
    {
        reboot();
        return;
    }
    else if (StringEqI(left,"RESET"))
    {
        reset();
        return;
    }
    else if (right == "")
    {
        my_error("expected rVal for command(%s)",left.c_str());
        return;
    }

    #ifdef ESP32
        if (StringEqI(left,"STA_SSID"))
        {
            preferences.putString("STA_SSID", right);
            String pass = preferences.getString("STA_PASS","");
            if (pass)
                connectWifi(right,pass);
            return;
        }
        else if (StringEqI(left,"STA_PASS"))
        {
            preferences.putString("STA_PASS", right);
            String ssid = preferences.getString("STA_SSID","");
            if (ssid)
                connectWifi(ssid,right);
            return;
        }
    #endif

    uint8_t found_cc = 0;
    for (uint8_t cc=SGTL_CC_BASE; cc<=SGTL_CC_MAX; cc++)
    {
        if (StringEqI(left,sgtl5000_getCCName(cc)))
        {
            found_cc = cc;
            break;
        }
    }

    if (!found_cc)
    {
        my_error("Unknown command(%s)=%s",left.c_str(),right.c_str());
        return;
    }


    uint8_t val=0;
    uint8_t max = sgtl5000_getCCMax(found_cc);
    if (!validInt(&val,left,right,max))
        return;

    // Send the Midi Message

    msgUnion msg(
        SGTL5000_CABLE,
        MIDI_TYPE_CC,
        SGTL5000_CHANNEL,
        found_cc,
        val);

    if (HUB_SERIAL_PORT.write(msg.b,4) != 4)
        my_error("Could not send Serial MIDI for command(%s)=%s",left.c_str(),right.c_str());

}



//---------------------------------------------
// test Serial Implementation
//---------------------------------------------

static char *bufferLine(Stream *stream, char *buf, int *len)
{
    while (stream->available())
    {
        char c = stream->read();
        // display(0,"stream got(%c)=0x%2x",(c>=' '?c:' '),c);

        if (c == 0x08)
        {
            if (*len)
                (*len)--;
        }
        else if (c == 0x0A || *len > MAX_STRING - 3)
        {
            buf[(*len)++] = 0;
            *len = 0;
            return buf;
        }
        else if (c && c != 0x0D && *len < MAX_STRING)
        {
            buf[(*len)++] = c;
        }
    }
    return 0;
}



static void processCommandLine(const char *line)
{
    // copy and strip out blanks

    String command;
    while (*line)
    {
        if (*line > ' ')
            command += *line;
        line++;
    }

    int delim = command.indexOf('=');
    bool dyadic = delim >= 0;
    String left = dyadic ? command.substring(0,delim) : command;
    String right = dyadic ? command.substring(delim+1) : "";
    handleCommand(left,right);
}



void testSerialImplementation()
{
    static int hub_serial_len = 0;
    static char hub_serial_buf[MAX_STRING+1];
    char *hub_line = bufferLine(
        &HUB_SERIAL_PORT,
        hub_serial_buf,
        &hub_serial_len);

    if (hub_line)
    {
        USB_SERIAL_PORT.println(hub_line);

        // telnet serial output slows loop() down too much
        // so there is a separate task to output a circular
        // buffer of telnet lines.

        #if defined(ESP32) && WITH_TELNET
            if (telnet_started && telnet_connected)
            {
                enqueTelnet(hub_line);
                // telnet.println(hub_line);
            }
        #endif
    }

    // process serial input to USB_SERIAL_PORT

    static int usb_serial_len = 0;
    static char usb_serial_buf[MAX_STRING+1];
    char *usb_line = bufferLine(
        &USB_SERIAL_PORT,
        usb_serial_buf,
        &usb_serial_len);
    if (usb_line)
    {
        processCommandLine(usb_line);
    }

    #if defined(ESP32) && WITH_TELNET
        if (telnet_started)
        {
            telnet.loop();
            static int telnet_serial_len = 0;
            static char telnet_serial_buf[MAX_STRING+1];
            char *telnet_line = bufferLine(
                &telnet,
                telnet_serial_buf,
                &telnet_serial_len);
            if (telnet_line)
            {
                processCommandLine(telnet_line);
            }
        }
    #endif

}




// serial.cpp
