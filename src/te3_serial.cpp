//-------------------------------------------
// te3_serial.cpp
//-------------------------------------------
//
// Debugging/Monitor output is not synchronized.
//
// Due to the "multi-threaded" TE3 architecture involving loop(), interrupts,
// and timer methods, there multiple threads can try to write to the output
// serial port(s) at the same time.
//
// Furthermore, I have never seen a good usage case for dircting the
// output from the monitor and/or other programs to the "other" serial
// port.  Most often I want to see them interleaved so that I can get
// an idea of the interactions and behavior, even if they are not in
// a string, first-in first-out order.
//
// This was also true on ESP32 programs and I have not even tested
// recent myDebug changes against the many existing ESP32 programs
// that use myDebug.
//
// "Its just debugging output" is one answer. Let it go. Live with it.
//
//--------------------------------------------------------------
// It is a bit difficult to explain the complexity herein and how
// that maps to the actual code.
//
// There are four bi-directional teensy Hardware Serial ports in use:
//
//      USB_SERIAL_PORT - connected to the USBC hub
//      DBG_SERIAL_PORT - the 1/8th in jack on the back of the box
//      RPI_SERIAL_PORT - connected to the rPi (Looper)
//      HUB_SERIAL_PORT - connected to the TE3_audio device (SGTL)
//
// and four (mostly output) streams which are logically mapped by prefs
// to be off (zero), or either the USB_SERIAL_PORT or the DBG_SERIAL_PORT:
//
//      TE3_DEBUG_STREAM - the main console.pm input/output stream
//      RPI_DEBUG_OUTPUT - where to send debug output from the rPi Looper
//      HUB_DEBUG_OUTPUT - where to send debug output from the TE3_audio device
//      MONITOR_OUTPUT - where to send output from the midi monitor
//
// These ports and streams are used in a plethora of different functions:
//
//      - Text Commands from the laptop like REBOOT, REBOOT_PI, REBOOT_AUDIO, etc
//      - rPi kernel (Looper kernel7.img) BINARY_UPLOADS from the laptop
//      - Bi-directional FILE_SYSTEM text protocol between the laptop and TE3
//      - Showing debugging output from this program (TE3)
//      - Showing debugging output from the TE3_audio (hub) program
//      - Showing debugging output from the rPi Looper program
//      - Bi-directional Serial Midi between TE3 and the rPi Looper program
//      - Bi-directional Serial Midi between TE3 and the TE3_audio program
//
// This code handles ALL INPUT from any of the hardware serial ports for
// all of the above functions.  OUTPUT to the hardware serial ports is
// a bit more complicated and this file only performs SOME of the output.
// For example, Serial midi commands FROM the TE3 to the rPi Looper are
// handled by direct writes to the RPI_SERIAL_PORT in midiQueue.cpp,
// whereas Serial midi coming from the rPi TO this TE3 program are
// processed herein.
//
//-------------------------------------------------------------------
// INPUT
//-------------------------------------------------------------------
// Because the TE3_DEBUG_STREAM can be mapped to be either the
// USB_SERIAL_PORT or the HUB_SERIAL_PORT (or be zero which means "off"),
// we actually only monitor three hardware serial ports for input.
//
//      TE3_DEBUG_STREAM - for input from the laptop (may be zero==Off)
//      RPI_SERIAL_PORT - for input from the rPi Looper program
//      HUB_SERIAL_PORT - for input from the TE3_audio program
//
// We separate the buffering of serial input from the processing of it
// to try to ensure that no incoming serial bytes are ever lost.
// The processing can take various amounts of time, and in practice
// the hardware serial ports do not, themselves, buffer enough bytes
// to ensure that we don't lose data while processing serial data.
//
// Therefore we use the fast (300 times per second) expSystem timer_handler()
// to call the pollSerial() method herein which merely reads and buffers
// the input from the above three streams.
//
// Then we allow the slow (20-50 times per second) main loop() function to
// call processSerial() method herein to process the buffers and/or call
// other functions in the system that can take varying amounts of time
// to complete.
//
//------------------------------------------------------------
// TE3_DEBUG_STREAM - INPUT and MODAL processing behavior
//------------------------------------------------------------
// The TE3_DEBUG_STREAM is synonymous with the stream that will be
// hooked to the console.pm program and which will initiate/handle
// kernel BINARY_UPLOADS and FILE_SYSTEM protocols.
//
//      - ctrl-B reboots the Pi
//      - ctrl-A is received from the console to enter "in_file_command" mode
//      - ctrl-E is received from the console to enter "in_upload_binary" mode
//
// This stream never contains serial midi messages.
//
//      - handles text commands performed by TE3 itself and/or
//        which are converted to serial midi and sent to the
//        TE3_audio device (HUB) or Looper (RPI).
//      - handles ctrl-B to reboot the rPi and ctrl-E bracketed
//        modal kernel BINARY_UPLOAD protocol
//      - handles FILE SYSTEM text protocol from the console,
//        working with the ctrl-A sent by console.pm to stay in
//        a mode when file system commands are in play.
//
// BINARY_UPLOAD and FILE_SYSTEM protocols are supported by modes
// which supercede normal processing of serial data buffers by
// setting flags ("in_upload_binary" or "in_file_command") which
// are cleared, by receiving a closing ctrl-E in the case of
// binary uploads, or by timeout since the last ctrl-A in the case
// of the file commands.
//
// Entering either of these modes turns off the MIDI_MONITOR
// and in the case of BINARY_UPLOAD also turns off the myDebug
// "dbgSerial" stream.  The streams are restaored when the mode
// is finished.
//
//-----------------------------------------------------------
// OUTPUT (Text)
//-----------------------------------------------------------
// Apart from the TE3_DEBUG_STREAM, the debugging text output from the
// rPi Looper program and TE3_audio (hub) program, as well as the
// text output from the midiMonitor, can be directed to one of the
// two output serial ports (USB or DBG), or turned "off" via prefs:
//
//      HUB_DEBUG_OUTPUT - where to send debug output from the TE3_audio device
//      RPI_DEBUG_OUTPUT - where to send debug output from the rPi Looper
//      MONITOR_OUTPUT - where to send output from the midi monitor
//


#include "defines.h"
#include <myDebug.h>
#include <teCommon.h>
#include <sgtl5000midi.h>
#include "commonDefines.h"
#include "expSystem.h"
#include "prefs.h"
#include "fileSystem.h"
#include "midiQueue.h"


#define dbg_cmd  0

#define DBG_RAW_SERIAL_MIDI_IN  1


#define MAX_STRING  255
#define SERIAL_BUF_SIZE         8192

#define SERIAL_PORT_NUM_TE3     0
#define SERIAL_PORT_NUM_HUB     1
#define SERIAL_PORT_NUM_RPI     2
#define NUM_INPUT_SERIAL_PORTS  3


#define FILE_COMMAND_TIMEOUT    12000   // maybe could be much shorter
#define CTRL_E_WINDOW           1000    // must be larger, accordingly, in console.pm

static bool in_file_command = 0;
static uint32_t file_command_time = 0;

static bool in_upload_binary = 0;
static Stream *SAVE_MONITOR = 0;
static Stream *saveDbgSerial = 0;


static void processCommandLine(const char *line);
    // forward


static const char *serialPortName(int serial_port_num)
    // debugging utility
{
    switch (serial_port_num)
    {
        case SERIAL_PORT_NUM_TE3 : return "TE3";
        case SERIAL_PORT_NUM_HUB : return "HUB";
        case SERIAL_PORT_NUM_RPI : return "RPI";
    }
    return "";
}



//----------------------------------
// circular buffers
//----------------------------------

typedef struct
{
    volatile uint16_t    head;
    volatile uint16_t    tail;
    uint8_t              *buf;   // padding bytes for debugging (write a zero after each read)
}   serialPortBuffer_t;


serialPortBuffer_t serial_buffer[NUM_INPUT_SERIAL_PORTS];
static volatile bool in_stream_poll;


void initStreamBuffers()
{
    display(0,"initStreamBuffers()",0);
    for (int i=0; i<NUM_INPUT_SERIAL_PORTS; i++)
        serial_buffer[i].buf = (uint8_t *) malloc(SERIAL_BUF_SIZE);
}



static void pollOne(int port_num)
    // as rapidly as possible, read and buffer all
    // available data from a stream into a cicrular buffer
{
    Stream *stream =
        port_num == SERIAL_PORT_NUM_RPI ? &RPI_SERIAL_PORT :
        port_num == SERIAL_PORT_NUM_HUB ? &HUB_SERIAL_PORT :
        TE3_DEBUG_STREAM;

    if (!stream)
        return;

    int avail = stream->available();
    if (avail)
    {
        int first_read = avail;
        int second_read = 0;

        serialPortBuffer_t *bbb = &serial_buffer[port_num];
        if (bbb->head + first_read > SERIAL_BUF_SIZE)
        {
            first_read = SERIAL_BUF_SIZE - bbb->head;
            second_read = avail - first_read;
            if (second_read >= bbb->head)
            {
                my_error("SERIAL_BUFFER_OVERFLOW ON STREAM(%d)",port_num);
                return;
            }
        }

        int got = stream->readBytes(&(bbb->buf[bbb->head]),first_read);
        if (got != first_read)
        {
            my_error("READ1(%d) FAILED WITH %d on SERIAL STREAM(%d)",first_read,got,port_num);
            return;
        }
        bbb->head += first_read;
        if (bbb->head >= SERIAL_BUF_SIZE)
            bbb->head = 0;

        if (second_read)
        {
            got = stream->readBytes(&(bbb->buf[bbb->head]),second_read);
            if (got != second_read)
            {
                my_error("READ2(%d) FAILED WITH %d on SERIAL STREAM(%d)",second_read,got,port_num);
                return;
            }
            bbb->head += second_read;
        }
    }
}


void pollStreams()
    // Called 300 times/second from expSystem::timer_handler()
{
    in_stream_poll = 1;
    for (int i=0; i<NUM_INPUT_SERIAL_PORTS; i++)
        pollOne(i);
    in_stream_poll = 0;
}


static int streamAvail(int port_num)
    // emulates Stream.available() method
{
    if (in_stream_poll)
        return 0;
    serialPortBuffer_t *bbb = &serial_buffer[port_num];
    int head = bbb->head;
    int tail = bbb->tail;
    if (head == tail)
        return 0;
    if (tail < head)
        return head-tail;
    return SERIAL_BUF_SIZE - tail + head;
}


static uint8_t streamRead(int port_num)
    // emulates Stream.read() method
{
    serialPortBuffer_t *bbb = &serial_buffer[port_num];
    int tail = bbb->tail++;
    uint8_t byte = bbb->buf[tail];
    if (bbb->tail >= SERIAL_BUF_SIZE)
        bbb->tail = 0;
    return byte;
}


#if 0
    // implemented, never tested
    static void streamReadBytes(int port_num, uint8_t *out_buf, int len)
        // emulates Stream.readBytes() method, but with no return value
    {
        serialPortBuffer_t *bbb = &serial_buffer[port_num];
        int tail = bbb->tail;
        uint8_t *in_buf = bbb->buf;

        int first_read = len;
        int second_read = 0;
        if (tail + first_read > SERIAL_BUF_SIZE)
        {
            first_read = SERIAL_BUF_SIZE - tail;
            second_read = len - first_read;
        }

        memcpy(out_buf,&in_buf[tail],first_read);
        if (second_read)
            memcpy(&out_buf[first_read],in_buf,second_read);
    }
#endif



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
                // TE3 Audio (my serial midi in general) always uses PORT0
                
                msgUnion msg(
                    0,
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



//=======================================================
// processSerial() implementation
//=======================================================

static char *bufferLine(int port_num, char *buf, int *len)
{
    while (streamAvail(port_num))
    {
        setTE3Busy();
        uint8_t byte = streamRead(port_num);

        // Input from TE3_DEBUG_STREAM does not contain
        // midi messages.  Special case ctrl characters
        // are handled here to enter modes and possibly
        // short return.
        //
        // When a mode is entered we turn off the MIDI_MONITOR
        // and possibly the myDebug dbgSerial stream.

        if (port_num == SERIAL_PORT_NUM_TE3)
        {
            if (byte == 0x01)       // ctrl-A
            {
                display(0,"got ctrl-A",0);
                if (!in_file_command)
                {
                    display(0,"starting in_file_command mode",0);
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
                // turn off the midi monitor and myDebug to make sure
                // they don't interfere with the binary upload.
                
                SAVE_MONITOR = MONITOR_OUTPUT;
                MONITOR_OUTPUT = 0;
                saveDbgSerial = dbgSerial;
                dbgSerial = 0;
                in_upload_binary = 1;
                return 0;
            }
        }

        // The other two ports give priority to serial midi
        // messages which are identified by an opening 0x0b
        // which never appears in plain text.

        else if (byte == 0x0b)     // midi message
        {
            uint8_t midi_msg[4];
            uint32_t *msg32 = (uint32_t *) midi_msg;
            *msg32 = byte;

            // memset(midi_msg,0,4);
            // midi_msg[0] = byte;

            int i=1;
            uint32_t timeout = micros();
            while (i<4)
            {
                uint32_t now = micros();
                if (streamAvail(port_num))
                {
                    midi_msg[i++] = streamRead(port_num);
                    timeout = now;
                }
                else if (now - timeout > 10000) // 10 ms
                {
                    i = 999;    // flag for timeout
                }
            }
            if (i==999)
            {
                my_error("timeout getting midi message",0);
                return 0;
            }

            #if DBG_RAW_SERIAL_MIDI_IN
                display(0,"--> %s MIDI: %02x %02x %02x %02x  msg32(0x%08x)",
                    serialPortName(port_num),
                    midi_msg[0],
                    midi_msg[1],
                    midi_msg[2],
                    midi_msg[3],
                    *msg32);
            #endif

            if (port_num == SERIAL_PORT_NUM_RPI)
            {
                theSystem.midiActivity(ACTIVITY_INDICATOR_RPI_IN);
                handleCommonMidiSerial(midi_msg);
                enqueuMonitor(MIDI_PORT_RPI,false,*msg32);
            }

            // The HUB_SERIAL_PORT does not yet currently
            // send serial midi messages, so this code is never
            // used.  It is implemented "for example", and notably
            // does not call handleCommonMidiSerial()

            else
            {
                theSystem.midiActivity(ACTIVITY_INDICATOR_HUB_IN);
                enqueuMonitor(MIDI_PORT_HUB,false,*msg32);
            }

            // continue processing any buffered available bytes

            continue;

        }   // done with 0x0b four byte midi message


        // Now we are processing regular text into cr/lf
        // delineated lines.  A backspace would only come
        // from the console in the TE3_DEBUG_STREAM

        if (byte == 0x08)   // backspace
        {
            if (*len)
                (*len)--;
        }
        else if (byte == 0x0A || *len > MAX_STRING - 3)
        {
            buf[(*len)++] = 0;
            *len = 0;

            // return the next line of text to be processed
            // to the caller.

            return buf;
        }
        else if (byte && byte != 0x0D && *len < MAX_STRING)
        {
            buf[(*len)++] = byte;
        }
    }

    // no complete line of text is ready so return zero

    return 0;

}   // bufferLine



static void processCommandLine(const char *line)
    // copy, strip out blanks, split into
    // left and right parts about equal sign,
    // and call handleCommand()
{
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





void processStreams()
{
    freeFileCommands();
        // This method has to be called somewhere fairly
        // often to cycle the two file command buffers
        // in fileCommand.cpp
        
    //---------------------------------------------
    // Serial processing modes
    //---------------------------------------------
    // Note that all serial midi processing and midi-monitor output
    // is halted while in_upload_binary or in_file_command

    if (in_upload_binary)
    {
        // forward everything between TE3_DEBUG_STREAM
        // and the RPI_SERIAL_PORT until a closing ctrl-E
        // is received.

        static uint32_t ctrl_E_time = 0;
        while (streamAvail(SERIAL_PORT_NUM_TE3))
        {
            uint8_t c = streamRead(SERIAL_PORT_NUM_TE3);
            if (c == 5)
                ctrl_E_time = millis();
            else
                ctrl_E_time = 0;
            RPI_SERIAL_PORT.write(c);
        }
        while (streamAvail(SERIAL_PORT_NUM_RPI))
        {
            uint8_t c = streamRead(SERIAL_PORT_NUM_RPI);
            if (TE3_DEBUG_STREAM)
                TE3_DEBUG_STREAM->write(c);
        }
        if (ctrl_E_time && millis() - ctrl_E_time > CTRL_E_WINDOW)
        {
            in_upload_binary = 0;
            display(0,"ending in_upload_binary mode",0);
            MONITOR_OUTPUT = SAVE_MONITOR;
            SAVE_MONITOR = 0;
            dbgSerial = saveDbgSerial;
            saveDbgSerial = 0;
        }
        return;
    }

    if (in_file_command)
    {
        // pass every character from TE3_DEBUG_STREAM to
        // the handleFileSystemChar() method until the
        // ctrl-A times out.
        //
        // The fileSystem itself will write directly to
        // the TE3_DEBUG stream as is needed.

        checkFileCommandTimeout();
        int avail = streamAvail(SERIAL_PORT_NUM_TE3);
        while (avail)
        {
            uint8_t c = streamRead(SERIAL_PORT_NUM_TE3);
            if (c == 0x01)      // ctrl-A
                display(0,"ignoring ctrl-A already in_file_command mode",0);
            else
            {
                // display(0,"te3s avail(%d) char(0x%02x)='%c'",avail,c,c>32?c:' ');
                handleFileSystemChar(0,(char)c);
            }
            file_command_time = millis();
            avail--;
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
    // process the SERIAL_PORT_NUM_RPI buffer

    static int rpi_serial_len = 0;
    static char rpi_serial_buf[MAX_STRING+1];
    char *rpi_line = bufferLine(
        SERIAL_PORT_NUM_RPI,
        rpi_serial_buf,
        &rpi_serial_len);
    if (rpi_line && RPI_DEBUG_OUTPUT)
    {
        RPI_DEBUG_OUTPUT->println(rpi_line);
    }

    // process the SERIAL_PORT_NUM_HUB buffer

    static int hub_serial_len = 0;
    static char hub_serial_buf[MAX_STRING+1];
    char *hub_line = bufferLine(
        SERIAL_PORT_NUM_HUB,
        hub_serial_buf,
        &hub_serial_len);
    if (hub_line && HUB_DEBUG_OUTPUT)
    {
        HUB_DEBUG_OUTPUT->println(hub_line);
    }

    // process the main TE3 DEBUG_SERIAL_PORT buffer
    // if the stream is not 0==Off

    if (TE3_DEBUG_STREAM)
    {
        static int usb_serial_len = 0;
        static char usb_serial_buf[MAX_STRING+1];
        char *usb_line = bufferLine(
            SERIAL_PORT_NUM_TE3,
            usb_serial_buf,
            &usb_serial_len);
        if (usb_line)
        {
            processCommandLine(usb_line);
        }
    }

    clearTE3Busy();
}


// end of te3_serial.cpp
