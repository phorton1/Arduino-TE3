//-------------------------------------------
// te3_serial.cpp
//-------------------------------------------
// There are four teensy Hardware Serial ports in use.
//
//      USB_SERIAL_PORT - connected to the USBC hub
//      DBG_SERIAL_PORT - the 1/8th in jack on the back of the box
//      HUB_SERIAL_PORT - connected to the TE3_audio device (SGTL)
//      RPI_SERIAL_PORT - connected to the rPi (Looper)
//
// and four streams which are logically mapped by prefs to be off (zero),
// or set to he USB or DBG serial ports.
//
//      TE3_DEBUG_STREAM - the main console.pm input/output stream
//      HUB_DEBUG_OUTPUT - where to send debug output from the TE3_audio device
//      RPI_DEBUG_OUTPUT - where to send debug output from the rPi Looper
//      MONITOR_OUTPUT - where to send output from the midi monitor
//
// The HUB and RPI Serial ports are read from directly, as they might
// contain functional serial midi messages, in addition to debugging
// output text from those two devices. If serial midi messages are
// found, they are always passed to the the expSystem for processing.
// Otherwise the output is optionally sent to the logically mapped
// DEBUB_OUTPUT stream.
//
// In a kernel BINARY_UPLOAD, the output from the rPi MUST be sent
// to the TE3_DEBUG_STREAM, and the setting of the RPI_DEBUG_OUTPUT
// is ignored.
//
// TE3_DEBUG_STREAM - INPUT
//
// Input from the USB or DBG Serial port is mapped by a pref
// into the TE3_DEBUG_STREAM, which can also be zero (turned off)
// It is synonymous with the stream that will be hooked to the
// console.pm program and which will initiate/handle kernel
// BINARY_UPLOADS and FILE_SYSTEM protocols.
//
// This stream never contains serial midi messages.
//
//      - handles text commands performed by TE3 itself and/or
//        which are converted to serial midi and sent to the
//        TE3_audio device (HUB) or Looper (RPI).
//      - handles ctrl-B to reboot the rPi and ctrl-E bracketed
//        kernel BINARY_UPLOAD protocol
//      - handles FILE SYSTEM commands from the console, including
//        currently IGNORING ctrl-A sent by console.pm, working
//        with the fileServer.cpp code
//
// OUTPUT (Text)
//
// Generally speaking the debugging (and midi monitor) text
// can be turned off, or directed to one of the two output
// serial ports (USB or DBG) via prefs:
//
//      HUB_DEBUG_OUTPUT - where to send debug output from the TE3_audio device
//      RPI_DEBUG_OUTPUT - where to send debug output from the rPi Looper
//      MONITOR_OUTPUT - where to send output from the midi monitor
//
// However, these mappings are IGNORED when in a BINARY_UPLOAD or
//      FILE_SYSTEM protocol, and in fact the MONITOR_OUTPUT will be
//      temporarily turned Off in these protocols.
//      In the BINARY_UPLOAD protocol, the RPI_SERIAL_PORT will be
//      used directly.
//
// NOTES on CONSOLE.PM and TE3_DEBUG_STREAM
//
// ctrl-B reboots the Pi
// ctrl-A is received from the console to enter "file_server_mode";
//
// The previous teensyPiLooper had no concept of handling anything itself,
//      and just forwarded everything from the USB Serial port to the rPi, so
//      no special "mode" was needed for kernel uploads .. just reboot and the
//      rest was handled by console.pm.
// To retain the notion that there are serial commands to TE3/TE3_auduio
//      meant that I had to identify when a serial kernel upload is
//      taking place.
// So, console.pm was modified to bracket binary uploads with a pair of ctrl-E's,
//      with a delay window around the closing one, that can be identified herein
//      to enter rPi kernel "binary_upload" mode, which takes complete precedence
//      over the serial port until the closing ctrl-E is received.
//
//-------------------------------------------------------
// COMBINING with fileSerial.cpp
//-------------------------------------------------------
//
// This is complicated by the fact that fileSerial.cpp currently parses
// character by character to build multi-line CR \n delimited fileServer commands
// and malloc() buffers, and not necessarily reading a "full line of text"
// including the closing LF \r.
//
// Perhaps we can take advantage of the ctrl-A sent by the console to say
// "hey, we're definitely in a fileServer mode" and in that case pass
// every character (with a 16 second timeout as in teensyPiLoooper)
// to the fileSerial.cpp::handleChar() method.



#include "defines.h"
#include <myDebug.h>
#include <teMIDI.h>
#include <teCommon.h>
#include <sgtl5000midi.h>
#include "commonDefines.h"
#include "expSystem.h"
#include "prefs.h"
#include "fileSystem.h"


#define dbg_cmd  0

#define MAX_STRING  255


#define SERIAL_PORT_NUM_TE3     0
#define SERIAL_PORT_NUM_HUB     1
#define SERIAL_PORT_NUM_RPI     2

#define FILE_COMMAND_TIMEOUT    12000   // maybe could be much shorter

static bool in_file_command = 0;
static uint32_t file_command_time = 0;

static bool in_upload_binary = 0;
static Stream *SAVE_MONITOR = 0;


static void processCommandLine(const char *line);
    // forward


static const char *serialPortName(int serial_port_num)
{
    switch (serial_port_num)
    {
        case SERIAL_PORT_NUM_TE3 : return "TE3";
        case SERIAL_PORT_NUM_HUB : return "HUB";
        case SERIAL_PORT_NUM_RPI : return "RPI";
    }
    return "";
}



//---------------------------------------------
// command atoms
//---------------------------------------------

static void reboot()
{
    warning(0,"REBOOTING TE3!!",0);
    delay(300);
    SCB_AIRCR = 0x05FA0004;
        // reboot teensy processors
}

static void reset()
{
    warning(0,"RESETTING TE3!!",0);
    delay(300);
    // unimplemented
    reboot();
}

static void rebootPi()
{
    display(0,"te3_serial::rebootPi() called",0);
    digitalWrite(PIN_LED_RPI_RUN,0);
    digitalWrite(PIN_LED_RPI_READY,0);
    digitalWrite(PIN_RPI_BOOT,1);
    // rpi_running = 0;
    // rpi_ready = 0;
    delay(900);
    digitalWrite(PIN_RPI_BOOT,0);
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
    for (uint16_t i=0; i<right.length(); i++)
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
    else if (StringEqI(left,"REBOOT_PI"))
    {
        rebootPi();
    }
    else if (StringEqI(left,"DUMP_LOOPER"))
    {
        display(0,"Sending LOOP_COMMAND_GET_STATE to rPi",0);
        uint8_t midi_message[4] = {
            0x0b,
            0xb0,
            LOOP_COMMAND_CC,
            LOOP_COMMAND_GET_STATE };
        RPI_SERIAL_PORT.write(midi_message,4);
    }


    // commands to TE3_audio or it's SGTL5000

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
            cable = AUDIO_CABLE;
            channel = AUDIO_CHANNEL;
            for (uint8_t cc=AUDIO_CC_BASE; cc<=AUDIO_CC_MAX; cc++)
            {
                if (StringEqI(left,audio_getCCName(cc)))
                {
                    found_cc = cc;
                    max = audio_getCCMax(found_cc);
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

    }   // commands to TE3_audio or it's SGTL5000
}   // handleCommand()



//---------------------------------------------
// handleSerial() Implementation
//---------------------------------------------
// I'm not sure a single method fits-all approach is in order here.
// At a minimum we need to know what port is in play and whether
// we are in a kernel upload or file_server mode for TE3 and the rPi.





static char *bufferLine(int serial_port_num, Stream *stream, char *buf, int *len)
{
    while (stream->available())
    {
        setTE3Busy();
        uint8_t byte = stream->read();
        // display(0,"stream got(%c)=0x%2x",(c>=' '?c:' '),c);

        if (serial_port_num == SERIAL_PORT_NUM_TE3)
        {
            if (byte == 0x01)       // ctrl-A
            {
                display(0,"got ctrl-A",0);
                if (!in_file_command)
                {
                    display(0,"starting in_file_command mode",0);
                    // turn off the midi monitor to make sure it doesn't
                    // interfere with the binary upload
                    SAVE_MONITOR = MONITOR_OUTPUT;
                    MONITOR_OUTPUT = 0;
                    in_file_command = 1;
                }
                file_command_time = millis();
            }
            else if (byte == 0x02)       // ctrl-B
            {
                rebootPi();
                return 0;
            }
            else if (byte == 0x05)       // ctrl-E
            {
                display(0,"starting in_upload_binary mode",0);
                // turn off the midi monitor to make sure it doesn't
                // interfere with the binary upload
                SAVE_MONITOR = MONITOR_OUTPUT;
                MONITOR_OUTPUT = 0;
                in_upload_binary = 1;
                return 0;
            }
        }
        else if (byte == 0x0b)     // midi message
        {
            uint8_t midi_msg[4];
            memset(midi_msg,0,4);
            midi_msg[0] = byte;

            uint32_t timeout = micros();

            int i=1;
            while (i<4)
            {
                uint32_t now = micros();
                if (stream->available())
                {
                    midi_msg[i++] = stream->read();
                    timeout = now;
                }
                else if (now - timeout > 10000) // 10 ms
                {
                    i = 999;
                }
            }

            if (i==999)
                my_error("timeout getting midi message",0);

            display(0,"--> %s MIDI: %02x %02x %02x %02x",
                serialPortName(serial_port_num),
                midi_msg[0],
                midi_msg[1],
                midi_msg[2],
                midi_msg[3]);

            if (serial_port_num == SERIAL_PORT_NUM_RPI)
            {
                handleCommonMidiSerial(midi_msg);
            }
        }


        if (byte == 0x08)
        {
            if (*len)
                (*len)--;
        }
        else if (byte == 0x0A || *len > MAX_STRING - 3)
        {
            buf[(*len)++] = 0;
            *len = 0;
            return buf;
        }
        else if (byte && byte != 0x0D && *len < MAX_STRING)
        {
            buf[(*len)++] = byte;
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
    freeFileCommands();
        // has to be called somewhere ...
        
    //---------------------------------------------
    // Serial processing modes
    //---------------------------------------------
    // Note that all serial message processing and midi-monitor output
    // is halted while in_upload_binary or in_file_command

    if (in_upload_binary)
    {
        static uint32_t ctrl_E_time = 0;
        while (TE3_DEBUG_STREAM->available())
        {
            uint8_t c = TE3_DEBUG_STREAM->read();
            if (c == 5)
                ctrl_E_time = millis();
            else
                ctrl_E_time = 0;
            RPI_SERIAL_PORT.write(c);
        }
        while (RPI_SERIAL_PORT.available())
        {
            uint8_t c = RPI_SERIAL_PORT.read();
            TE3_DEBUG_STREAM->write(c);
        }
        if (ctrl_E_time && millis() - ctrl_E_time > 200)
        {
            in_upload_binary = 0;
            display(0,"ending in_upload_binary mode",0);
            // turn the midi monitor back on (or back to whatever
            // it is set to by prefs)
            MONITOR_OUTPUT = SAVE_MONITOR;
            SAVE_MONITOR = 0;

        }
        return;
    }

    if (in_file_command)
    {
        checkFileCommandTimeout();
        while (TE3_DEBUG_STREAM->available())
        {
            uint8_t c = TE3_DEBUG_STREAM->read();
            if (c == 0x01)      // ctrl-A
                display(0,"ignoring ctrl-A already in_file_command mode",0);
            else
                handleFileSystemChar(0,(char)c);
            file_command_time = millis();
        }
        if (file_command_time &&
            millis() - file_command_time > FILE_COMMAND_TIMEOUT)
        {
            file_command_time = 0;
            in_file_command = 0;
            display(0,"ending in_file_command mode",0);
            MONITOR_OUTPUT = SAVE_MONITOR;
            SAVE_MONITOR = 0;
        }
        return;
    }


    //---------------------------------------------
    // normal processing
    //---------------------------------------------
    // process RPI_SERIAL_PORT

    static int rpi_serial_len = 0;
    static char rpi_serial_buf[MAX_STRING+1];
    char *rpi_line = bufferLine(
        SERIAL_PORT_NUM_RPI,
        &RPI_SERIAL_PORT,
        rpi_serial_buf,
        &rpi_serial_len);
    if (rpi_line)
    {
        RPI_DEBUG_OUTPUT->println(rpi_line);
    }

    // process HUB_SERIAL_PORT

    static int hub_serial_len = 0;
    static char hub_serial_buf[MAX_STRING+1];
    char *hub_line = bufferLine(
        SERIAL_PORT_NUM_HUB,
        &HUB_SERIAL_PORT,
        hub_serial_buf,
        &hub_serial_len);
    if (hub_line)
    {
        HUB_DEBUG_OUTPUT->println(hub_line);
    }

    // process the main TE3 DEBUG_SERIAL_PORT

    static int usb_serial_len = 0;
    static char usb_serial_buf[MAX_STRING+1];
    char *usb_line = bufferLine(
        SERIAL_PORT_NUM_TE3,
        TE3_DEBUG_STREAM,
        usb_serial_buf,
        &usb_serial_len);
    if (usb_line)
    {
        processCommandLine(usb_line);
    }
    clearTE3Busy();
}

