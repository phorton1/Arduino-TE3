//-------------------------------------------
// te3_serial.cpp
//-------------------------------------------
// Handles up to 4 Serial Ports with some capabilities to
// be turned on/off and/or driven by preferences.
//
//      USB_SERIAL_PORT
//          typically the main debugging serial port to console.pm
//          - provides display() debug output from TE3 itself
//          - consolidates debug output from RPI and the HUB
//          - handles text commands to TE3 itself
//          - handles commands to HUB by sending serial midi to it
//          - handles rPI kernel uploads to the RPI_SERIAL port
//          - handles FileSystem commands for the TE3 SD card
//          - typically displays Midi monitor output
//      DBG_SERIAL_PORT
//          an alternative 3 pin output serial port that can
//              do all of the things the USB_SERIAL_PORT can do for
//              debugging the TE3 in-vitro while the usbC hub is hooked
//              up to an iPad
//          can also perhaps be used as a way to separate debug output
//              streams to two different console invocations, i.e. separating
//              midi-monitoring from debugging output, or focusing on one
//              device in particular
//      RPI_SERIAL_PORT
//          - sends debugging output from the Looper/circle program(s)
//          - sends serial midi, mostly to TE3 from the Looper program
//          - accepts serial midi to control the Looper program
//          - can accept binary file kernel uploads during bootstrap phase
//      HUB_SERIAL_PORT
//          - sends debugging oiutput from the TE3_audio device including
//            "dumps" of the SGTL5000 and TE3_audio device states
//          - accepts serial midi to constrol the TE3_audio device,
//            mixers, reboot, etc, and to configure the SGTL5000
//
// This could get exceedingly complicated, esp if we have to, for example,
// route serial midi messages of specific types between the rPi Looper and
// the teensy4.0 SGTL audio device.
//
// For now this is prototype code, starting with the ability to reboot the
//      rPi on ctrl-B.
// ctrl-A is received from the console to enter "file_server_mode";
//
// The previous teensyPiLooper had no concept of handling anything itself,
//      and just forwarded everything from the USB Serial port to the rPi, so
//      no special "mode" was needed for kernel uploads .. just reboot and the
//      rest was handled by console.pm.
// I'd like to retain the notion that there are serial commands to TE3/TE3_auduio
//      which means I will have to identify when a serial kernel upload is
//      taking place.
// We *could* see if the RPI sends my $KERNEL_UPLOAD_RE = 'Press <space> within 3 seconds to upload file';
//      and check if the USB port responds with a space in that window to "enter" a mode, but then
//      getting out of the mode would be problematic.
// Alternatively could add yet another param to console that says "this is Looper3, so send ctrl-E
//      to bracket rPI uploads.
// For now I'm gonna TEMPORARILY modify console.pm to bracket binary uploads with a pair of ctrl-E's
// In either case we have the issue of sending ctrl-A, B, or E within the binary upload itself which
//      was typically handled by isolating those using a timer.



#include "defines.h"
#include <myDebug.h>
#include <teMIDI.h>
#include <teCommon.h>
#include <sgtl5000midi.h>
#include "commonDefines.h"
#include "expSystem.h"
#include "prefs.h"


#define dbg_cmd  0

#define MAX_STRING  255


static void processCommandLine(const char *line);
    // forward


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

#define SERIAL_PORT_NUM_TE3     0
#define SERIAL_PORT_NUM_HUB     1
#define SERIAL_PORT_NUM_RPI     2

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



static bool in_upload_binary = 0;



static char *bufferLine(int serial_port_num, Stream *stream, char *buf, int *len)
{
    while (stream->available())
    {
        setTE3Busy();
        uint8_t byte = stream->read();
        // display(0,"stream got(%c)=0x%2x",(c>=' '?c:' '),c);

        if (serial_port_num == SERIAL_PORT_NUM_TE3)
        {
            if (byte == 0x02)      // ctrl-B
            {
                rebootPi();
                return 0;
            }
            if (byte == 0x05)       // ctrl-E
            {
                display(0,"starting in_upload_binary mode",0);
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
    // extern Stream *TE3_DEBUG_STREAM;
    // extern Stream *HUB_DEBUG_OUTPUT;
    // extern Stream *RPI_DEBUG_OUTPUT;

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
        }
        return;
    }


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

