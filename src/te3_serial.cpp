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

#include "defines.h"
#include <myDebug.h>
#include <teMIDI.h>
#include <teCommon.h>
#include <sgtl5000midi.h>
#include <nvs_flash.h>


#define dbg_cmd  0
#define dbg_telnet 0


#define MAX_STRING  255



static void processCommandLine(const char *line);
    // forward


//-----------------------------------------
// telnet
//-----------------------------------------

#if WITH_WIFI && WITH_TELNET

    #define MAX_TELNET_STRINGS   1000

    ESPTelnetStream telnet;
    bool telnet_started = false;

    static volatile int telnet_head = 0;
    static volatile int telnet_tail = 0;
    static String telnet_queue[MAX_TELNET_STRINGS];
    static bool telnet_connected = false;


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

    // TE3 commands

    if (StringEqI(left,"REBOOT"))
    {
        reboot();
    }
    else if (StringEqI(left,"RESET"))
    {
        reset();
    }
    #if WITH_WIFI
        else if (StringEqI(left,"STA_SSID"))
        {
            preferences.putString("STA_SSID", right);
            String pass = preferences.getString("STA_PASS","");
            if (pass)
                connectWifi(right,pass);
        }
        else if (StringEqI(left,"STA_PASS"))
        {
            preferences.putString("STA_PASS", right);
            String ssid = preferences.getString("STA_SSID","");
            if (ssid)
                connectWifi(ssid,right);
        }
    #endif

    // commands to TE3_hub or it's SGTL5000

    else
    {
        uint8_t val = 0;
        uint8_t found_cc = 0;
        uint8_t cable = SGTL5000_CABLE;
        uint8_t channel = SGTL5000_CHANNEL;
        uint8_t max = 255;

        for (uint8_t cc=SGTL_CC_BASE; cc<=SGTL_CC_MAX; cc++)
        {
            if (StringEqI(left,sgtl5000_getCCName(cc)))
            {
                found_cc = cc;
                max = sgtl5000_getCCMax(found_cc);
                break;
            }
        }

        if (!found_cc)
        {
            cable = TEHUB_CABLE;
            channel = TEHUB_CHANNEL;
            for (uint8_t cc=TEHUB_CC_BASE; cc<=TEHUB_CC_MAX; cc++)
            {
                if (StringEqI(left,tehub_getCCName(cc)))
                {
                    found_cc = cc;
                    max = tehub_getCCMax(found_cc);
                    break;
                }
            }
        }

        if (found_cc)
        {
            if (max != 255 && right == "")
            {
                my_error("expected rVal for command(%s)",left.c_str());
            }
            else if (max == 255 || validInt(&val,left,right,max))
            {
                // Send the Midi Message

                msgUnion msg(
                    cable,
                    MIDI_TYPE_CC,
                    channel,
                    found_cc,
                    val);

                if (HUB_SERIAL_PORT.write(msg.b,4) != 4)
                {
                    my_error("Could not send Serial MIDI for command(%s)=%s",left.c_str(),right.c_str());
                }
            }
        }
        else    // !found_cc
        {
            my_error("Unknown command(%s)=%s",left.c_str(),right.c_str());
        }

    }   // commands to TE3_hub or it's SGTL5000
}   // handleCommand()



//---------------------------------------------
// handleSerial() Implementation
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



void handleSerial()
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

        #if WITH_WIFI && WITH_TELNET
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

    #if WITH_WIFI && WITH_TELNET
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

