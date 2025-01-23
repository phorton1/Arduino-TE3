//-------------------------------------------
// te3_serial.cpp
//-------------------------------------------
// Serial Port and Command Line handler

#include "defines.h"
#include <myDebug.h>
#include <teMIDI.h>
#include <teCommon.h>
#include <sgtl5000midi.h>

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
    // process HUB_SERIAL_PORT

    static int hub_serial_len = 0;
    static char hub_serial_buf[MAX_STRING+1];
    char *hub_line = bufferLine(
        &HUB_SERIAL_PORT,
        hub_serial_buf,
        &hub_serial_len);
    if (hub_line)
    {
        USB_SERIAL_PORT.println(hub_line);
    }

    // process USB_SERIAL_PORT

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
}

