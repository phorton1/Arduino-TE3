//------------------------------------------------------
// midiMonitor.cpp
//------------------------------------------------------
// This monitor is separate and completely decoupled from the
// actual needed FTP processing that takes place in midiQueue.cpp
// This decoupling means that (a) there is a lot of very similar
// code here as we parse all the same messages again, and
// (b) messages may show up in the monitor AFTER they have been
// processed in midiQueue.cpp.


#include "myDebug.h"
#include "midiQueue.h"
#include "ftp.h"
#include "ftp_defs.h"
#include "commonDefines.h"


#define DEBUG_MONITOR_QUEUE     0
#define DEBUG_MONITOR           0

#define DBG_COLOR               "\033[96m"       // bright cyan


#define MAX_MONITOR_QUEUE    8192
#define MAX_SYSEX_BUFFER    1024

static volatile int monitor_head;
static volatile int monitor_tail;
static uint32_t monitor_queue[MAX_MONITOR_QUEUE];

int sysex_buflen[NUM_MIDI_PORTS]     = {0,0,0,0,0,0,0,0};
uint8_t sysex_buffer[NUM_MIDI_PORTS][MAX_SYSEX_BUFFER];


static void _monitor(msgUnion &msg);
    // forward


void enqueuMonitor(int port, bool output, uint32_t msg32)
    // enqueue a completely setup msgUnion for monitoring
{
    // short returns based on monitor prefs

    if (!MONITOR_OUTPUT)
        return;

    msgUnion msg(msg32);
    msg.setPort(port);
    if (output)
        msg.setOutput();

    int port_enum = msg.portEnum();
    int channel = msg.channel() - 1;

    if (!output && !getPref8(PREF_MONITOR_USB1_IN + port_enum))
        return;
    if (output && !getPref8(PREF_MONITOR_USB1_OUT + port_enum))
        return;
    if (!getPref8(PREF_MONITOR_CHANNEL1 + channel))
        return;
    if (msg.isActiveSense() && !getPref8(PREF_MONITOR_ACTIVESENSE))
        return;
    

    #if DEBUG_MONITOR_QUEUE
        display_color(DBG_COLOR,0,"enqueueMonitor port(0x%02x) msg32(0x%08x) head(%d) tail(%d)",port,msg32,monitor_head,monitor_tail);
    #endif

    __disable_irq();
    monitor_queue[monitor_head++] = msg.i;
    if (monitor_head == MAX_MONITOR_QUEUE)
        monitor_head = 0;
    if (monitor_head == monitor_tail)
        my_error("enqueuMonitor() overflow at %d",monitor_head);
    __enable_irq();
}



void dequeueMonitor()
    // dequeue and display monitor messages
{
    if (monitor_tail != monitor_head)
    {
        #if DEBUG_MONITOR_QUEUE
            display_color(DBG_COLOR,0,"dequeueMonitor(0x%08x) head(%d) tail(%d)",monitor_queue[monitor_tail],monitor_head,monitor_tail);
        #endif

		__disable_irq();
        uint32_t msg32 = monitor_queue[monitor_tail++];
        if (monitor_tail == MAX_MONITOR_QUEUE)
            monitor_tail = 0;
		__enable_irq();

        msgUnion msg(msg32);
        _monitor(msg);
    }
}


//-------------------------------------
// Utilities
//-------------------------------------

static const char *portName(const msgUnion &msg)
{
    if (msg.isOutput())
    {
        switch (msg.port())
        {
            case MIDI_PORT_USB1  : return "USB1_OUT";
            case MIDI_PORT_USB2  : return "USB2_OUT";
            case MIDI_PORT_USB3  : return "USB3_OUT";
            case MIDI_PORT_USB4  : return "USB4_OUT";
            case MIDI_PORT_HOST1 : return "HOST1_OUT";
            case MIDI_PORT_HOST2 : return "HOST2_OUT";
            case MIDI_PORT_RPI   : return "RPI_OUT";
            case MIDI_PORT_HUB   : return "HUB_OUT";
        }
    }
    else
    {
        switch (msg.port())
        {
            case MIDI_PORT_USB1  : return "USB1_IN";
            case MIDI_PORT_USB2  : return "USB2_IN";
            case MIDI_PORT_USB3  : return "USB3_IN";
            case MIDI_PORT_USB4  : return "USB4_IN";
            case MIDI_PORT_HOST1 : return "HOST1_IN";
            case MIDI_PORT_HOST2 : return "HOST2_IN";
            case MIDI_PORT_RPI   : return "RPI_IN";
            case MIDI_PORT_HUB   : return "HUB_IN";
        }
    }
    return "UNKNOWN PORT";
}



static const char *getStandardCCName(int i)
   // from http://www.nortonmusic.com/midi_cc.html
{
    if (i==0  ) return "Bank Select (MSB)";
    if (i==1  ) return "Modulation Wheel";
    if (i==2  ) return "Breath controller";
    if (i==4  ) return "Foot Pedal (MSB)";
    if (i==5  ) return "Portamento Time (MSB)";
    if (i==6  ) return "Data Entry (MSB)";
    if (i==7  ) return "Volume (MSB)";
    if (i==8  ) return "Balance (MSB)";
    if (i==10 ) return "Pan position (MSB)";
    if (i==11 ) return "Expression (MSB)";
    if (i==12 ) return "Effect Control 1 (MSB)";
    if (i==13 ) return "Effect Control 2 (MSB)";
    if (i==16 ) return "General Purpose Slider 1";
    if (i==17 ) return "Knob 1 or General Purpose Slider 2";
    if (i==18 ) return "General Purpose Slider 3";
    if (i==19 ) return "Knob 2 General Purpose Slider 4";
    if (i==20 ) return "Knob 3";
    if (i==21 ) return "Knob 4";
    if (i==32 ) return "Bank Select (LSB) (see cc0)";
    if (i==33 ) return "Modulation Wheel (LSB)";
    if (i==34 ) return "Breath controller (LSB)";
    if (i==36 ) return "Foot Pedal (LSB)";
    if (i==37 ) return "Portamento Time (LSB)";
    if (i==38 ) return "Data Entry (LSB)";
    if (i==39 ) return "Volume (LSB)";
    if (i==40 ) return "Balance (LSB)";
    if (i==42 ) return "Pan position (LSB)";
    if (i==43 ) return "Expression (LSB)";
    if (i==44 ) return "Effect Control 1 (LSB)";
    if (i==45 ) return "Effect Control 2 (LSB)";
    if (i==64 ) return "Hold Pedal (on/off)";
    if (i==65 ) return "Portamento (on/off)";
    if (i==66 ) return "Sustenuto Pedal (on/off)";
    if (i==67 ) return "Soft Pedal (on/off)";
    if (i==68 ) return "Legato Pedal (on/off)";
    if (i==69 ) return "Hold 2 Pedal (on/off)";
    if (i==70 ) return "Sound Variation";
    if (i==71 ) return "Resonance (aka Timbre)";
    if (i==72 ) return "Sound Release Time";
    if (i==73 ) return "Sound Attack Time";
    if (i==74 ) return "Frequency Cutoff (aka Brightness)";
    if (i==75 ) return "Sound Control 6";
    if (i==76 ) return "Sound Control 7";
    if (i==77 ) return "Sound Control 8";
    if (i==78 ) return "Sound Control 9";
    if (i==79 ) return "Sound Control 10";
    if (i==80 ) return "Decay or General Purpose Button 1";
    if (i==81 ) return "Hi Pass Filter Frequency or General Purpose Button 2";
    if (i==82 ) return "General Purpose Button 3";
    if (i==83 ) return "General Purpose Button 4";
    if (i==91 ) return "Reverb Level";
    if (i==92 ) return "Tremolo Level";
    if (i==93 ) return "Chorus Level";
    if (i==94 ) return "Celeste Level or Detune";
    if (i==95 ) return "Phaser Level";
    if (i==96 ) return "Data Button increment";
    if (i==97 ) return "Data Button decrement";
    if (i==98 ) return "Non-registered Parameter (LSB)";
    if (i==99 ) return "Non-registered Parameter (MSB)";
    if (i==100) return "Registered Parameter (LSB)";
    if (i==101) return "Registered Parameter (MSB)";
    if (i==120) return "All Sound Off";
    if (i==121) return "All Controllers Off";
    if (i==122) return "Local Keyboard (on/off)";
    if (i==123) return "All Notes Off";
    if (i==124) return "Omni Mode Off";
    if (i==125) return "Omni Mode On";
    if (i==126) return "Mono Operation";
    if (i==127) return "Poly Operation";
    return "undefined";
}



static const char *LOOPER_CTRL_NAMES[LOOPER_NUM_CONTROLS] = {
    "INPUT_GAIN",
    "THRU_VOLUME",
    "LOOP_VOLUME",
    "MIX_VOLUME",
    "OUTPUT_GAIN"};

static const char *trackStateString(uint8_t p2)
{
    static char buf[64];
    buf[0] = 0;

    if (p2 == TRACK_STATE_EMPTY)
        strcpy(buf,"EMPTY");
    else if (p2 == TRACK_STATE_STOPPED)
        strcpy(buf,"STOPPED");
    else
    {
        if (p2 & TRACK_STATE_RECORDING)           // 0x0001
            strcat(buf,"RECORD ");
        if (p2 & TRACK_STATE_PLAYING)             // 0x0002
            strcat(buf,"PLAY ");
        if (p2 & TRACK_STATE_PENDING_RECORD)      // 0x0008
            strcat(buf,"PEND_RECORD ");
        if (p2 & TRACK_STATE_PENDING_PLAY)        // 0x0010
            strcat(buf,"PEND_PLAY ");
        if (p2 & TRACK_STATE_PENDING_STOP)        // 0x0020
            strcat(buf,"PEND_STOP ");
    }
    return buf;
}




static void getLooperCommandDescrip(char *buf,uint8_t p1,uint8_t p2)
{
    #define TRACKS_X_LAYERS (LOOPER_NUM_TRACKS * LOOPER_NUM_LAYERS)

    sprintf(buf,"unknown Looper CC");

    if (p1 == LOOP_COMMAND_CC)                  // 0x01		// send     recv        the value is the LOOP command
    {
        strcpy(buf,"LOOP_COMMAND: ");

        if (p2 == LOOP_COMMAND_CLEAR_ALL)                   // 0x01
            strcat(buf,"CLEAR_ALL");
        else if (p2 == LOOP_COMMAND_STOP_IMMEDIATE)         // 0x02      // stop the looper immediately
            strcat(buf,"STOP_IMMEDIATE");
        else if (p2 == LOOP_COMMAND_STOP)                   // 0x03      // stop at next cycle point
            strcat(buf,"STOP");
        else if (p2 == LOOP_COMMAND_DUB_MODE)               // 0x04      // the dub mode is handled by rPi and modeled here
            strcat(buf,"DUB");
        else if (p2 == LOOP_COMMAND_ABORT_RECORDING)        // 0x06      // abort the current recording if any
            strcat(buf,"ABORT_RECORDING");
        else if (p2 == LOOP_COMMAND_LOOP_IMMEDIATE)         // 0x08      // immediatly loop back to all clip starts ...
            strcat(buf,"LOOP_IMMEDIATE");
        else if (p2 == LOOP_COMMAND_SET_LOOP_START)         // 0x09      // immediatly set the "restart point" for the clips in the track
            strcat(buf,"SET_LOOP_START");
        else if (p2 == LOOP_COMMAND_CLEAR_LOOP_START)       // 0x0A      // immediatly set the "restart point" for the clips in the track
            strcat(buf,"CLEAR_LOOP_START)");
        else if (p2 >= LOOP_COMMAND_TRACK_BASE &&           // 0x10      // there are 16 possible "track" buttons but CLIP CC's spaces limit it
                 p2 <  LOOP_COMMAND_TRACK_BASE + 16)
            sprintf(&buf[strlen(buf)],"TRACK_%d",p2 - LOOP_COMMAND_TRACK_BASE);
        else if (p2 == LOOP_COMMAND_ERASE_TRACK_BASE)       // 0x20      // erase the given track (stops it if playing)
            sprintf(&buf[strlen(buf)],"ERASE_TRACK_%d",p2 - LOOP_COMMAND_ERASE_TRACK_BASE);
        else if (p2 == LOOP_COMMAND_GET_STATE)		        // 0x30	    // NEW the looper will dump all state
            strcat(buf,"GET_STATE");
        else
            strcat(buf,"UNKNOWN");
    }
    else if (p1 == LOOP_STOP_CMD_STATE_CC)      // 0x02		// recv     send        the value is 0, LOOP_COMMAND_STOP or STOP_IMMEDIATE
    {
         strcpy(buf,"STOP_BUTTON: ");
         if (p2 == 0)
            strcat(buf,"Off");
         else if (p2 == LOOP_COMMAND_STOP)
            strcat(buf,"STOP");
         else if (p2 == LOOP_COMMAND_STOP_IMMEDIATE)
            strcat(buf,"STOP_IMMEDIATE");
         else
            strcat(buf,"UNKNOWN");
    }
    else if (p1 == LOOP_DUB_STATE_CC)           // 0x03		// recv     send        value is currently only the DUB state
        sprintf(buf,"DUB_STATE: %s",p2?"ON":"off");
    else if (p1 == NOTIFY_LOOP)                 // 0x05     // recv     send        value=number of pending loop notifies
        sprintf(buf,"NOTIFY_LOOP: pending(%d)",p2);
    else if (p1 >= LOOP_CONTROL_BASE_CC &&      // 0x08     // send     recv        RANGED for 0..LOOPER_NUM_CONTROLS the value is the volume control (Looper pedal == 0x67)
             p1 <  LOOP_CONTROL_BASE_CC + LOOPER_NUM_CONTROLS)
        sprintf(buf,"CTRL %s=%d",LOOPER_CTRL_NAMES[p1 - LOOP_CONTROL_BASE_CC],p2);
    else if (p1 >= TRACK_STATE_BASE_CC &&       // 0x10		// recv     send        RANGED for NUM_TRACKS, upto 16 tracks, value is track state
             p1 <  TRACK_STATE_BASE_CC + 16)
        sprintf(buf,"TRACK_STATE[%d] = %s",p1 - TRACK_STATE_BASE_CC,trackStateString(p2));
    else if (p1 >= CLIP_VOL_BASE_CC &&          // 0x20		// both     both        RANGED for NUM_TRACKS * NUM_LAYERS, upto 32 total - value is the clip volume
             p1 <  CLIP_VOL_BASE_CC + TRACKS_X_LAYERS)
    {
        uint8_t clip = p1 - CLIP_VOL_BASE_CC;
        uint8_t track = clip / LOOPER_NUM_LAYERS;
        uint8_t layer = clip % LOOPER_NUM_LAYERS;
        sprintf(buf,"CLIP(%d,%d) VOL=%d",track,layer,p2);
    }
    else if (p1 >= CLIP_MUTE_BASE_CC &&         // 0x40		// both     both        RANGED for NUM_TRACKS * NUM_LAYERS, upto 24 total - value is mute state
             p1 <  CLIP_MUTE_BASE_CC + TRACKS_X_LAYERS)
    {
        uint8_t clip = p1 - CLIP_MUTE_BASE_CC;
        uint8_t track = clip / LOOPER_NUM_LAYERS;
        uint8_t layer = clip % LOOPER_NUM_LAYERS;
        sprintf(buf,"CLIP(%d,%d) MUTE=%d",track,layer,p2);
    }
}


//-----------------------------------------------
// the monitor
//-----------------------------------------------
// The use of colors is complicated, esp inasmuch as we foreground
// and background colors to play with.
//
// My first thought is to assign each port a different color,
// so that you can easily see what is coming from (or going
// to each port) just based on the color.
//
// Previously I used colors to separate message types.
// Ignoring the fact that I am using light_cyan for the DEBUG_MONITOR debugging itself.
// I will use a background of BLUE for incoming, and BROWN for outgoing messages
// with LIGHT colors on top of that by port.


static void _monitor(msgUnion &msg)
{
    #if DEBUG_MONITOR
        display_color(DBG_COLOR,0,"_monitor(0x%08x) port(0x%02x) output(%d) channel(%d) type(0x%02x) p1(0x%02x) p2(0x%02x)",
            msg.i,
            msg.port(),
            msg.isOutput(),
            msg.channel(),
            msg.type(),
            msg.param1(),
            msg.param2());
    #endif

    static uint8_t last_ftp_cmd[2];     // one for the input port, and one for the output port


    const char *port_name = portName(msg);
    int port = msg.port();
    int port_enum = msg.portEnum();
    uint8_t type = msg.type();
    uint8_t p0 = msg.b[1];              // raw byte used for sysex parsing
    uint8_t p1 = msg.param1();
    uint8_t p2 = msg.param2();
    
    bool is_ftp = msg.port() == FTP_ACTIVE_PORT;
    bool is_ftp_in = is_ftp && !msg.isOutput();

    #if DEBUG_MONITOR
        display_color(DBG_COLOR,0,"    port_name(%s) type(0x%02x) p0(0x%02x) p1(0x%02x) p2(0x%02x) is_ftp(%d) is_ftp_in(%d)",
            port_name,
            type,
            p0,
            p1,
            p2,
            is_ftp,
            is_ftp_in);
    #endif


    char buf2[100] = {0};
    int bg_color = msg.isOutput() ? ansi_color_bg_red : ansi_color_bg_blue;
    int fg_color =
        port <= MIDI_PORT_USB4 ? ansi_color_white :
        port <= MIDI_PORT_HOST2 ? ansi_color_light_cyan :
        port == MIDI_PORT_RPI ? ansi_color_yellow :
        ansi_color_black;


    //--------------------------------
    // buffer SYSEX
    //--------------------------------
    // FTP seems to start all sysex's with 0x14
    // and end them with 0x15, 0x16, or 0x17.

    if (type >= 0x04 && type <= 0x07)
    {
        int len = 3;
        bool is_done = 0;
        uint8_t *buf = sysex_buffer[port_enum];
        int buf_len = sysex_buflen[port_enum];

        if (type == 0x04)        // start midi message
        {
            if (!buf_len && p0 != 0xf0)
                warning(0,"sysex does not start with F0 got(%02x)",p0);
        }
        else                    // end midi message
        {
            is_done = 1;
            len = type - 0x4;
        }

        uint8_t *ip = msg.b + 1;
        uint8_t *op = &buf[buf_len];
        while (len--)
        {
            *op++ = *ip++;
            buf_len++;
        }
        sysex_buflen[port_enum] = buf_len;

        if (is_done)
        {
            sysex_buflen[port_enum] = 0;
            if (buf[buf_len-1] != 0xf7)
                warning(0,"sysex does not end with F7",0);

            int show_sysex = getPref8(PREF_MONITOR_SYSEX);
            if (show_sysex)
            {
                sprintf(buf2,"\033[%d;%dm%s(%d) sysex len=%d",
                    fg_color,
                    bg_color,
                    port_name,
                    port_enum,
                    buf_len);
                MONITOR_OUTPUT->println(buf2);

                if (getPref8(PREF_MONITOR_PARSE_FTP_PATCHES))
                    showFtpPatch(MONITOR_OUTPUT,fg_color,bg_color,is_ftp_in,buf,buf_len);

                if (show_sysex == 2)
                    display_bytes_long(0,0,buf,buf_len,MONITOR_OUTPUT);

            }   // show_sysex
        }   // is_done

        return;
    }


    // NON-SYSEX messages

    bool show_it = 0;
    const char *s = "unknown msg!!";

    if (type == MIDI_TYPE_NOTE_OFF)     // 0x08
    {
        if (getPref8(PREF_MONITOR_NOTE_OFF))
        {
            s = "Note Off";
            show_it = 1;
        }
    }
    else if (type == MIDI_TYPE_NOTE_ON)     // 0x09
    {
        if (getPref8(PREF_MONITOR_NOTE_ON))
        {
            s = "Note On";
            show_it = 1;
        }
    }
    else if (type == MIDI_TYPE_VELOCITY)    // 0x0a
    {
        if (getPref8(PREF_MONITOR_VELOCITY))
        {
            s = "VelocityChange";   // after touch poly
            show_it = 1;
        }
    }
    else if (type == MIDI_TYPE_PGM_CHG)     // 0x0c
    {
        if (getPref8(PREF_MONITOR_PROGRAM_CHG))
        {
            s = "ProgramChange";
            show_it = 1;
        }
    }
    else if (type == MIDI_TYPE_AFTERTOUCH)  // 0x0d
    {
        if (getPref8(PREF_MONITOR_AFTERTOUCH))
        {
            s = "AfterTouch";
            show_it = 1;
        }
    }
    else if (type == MIDI_TYPE_PITCHBEND)   // 0x0E
    {
        if (getPref8(PREF_MONITOR_PITCHBEND))
        {
            s = "Pitch Bend";
            int value = p1 + (p2 << 7);
            value -= 8192;
            sprintf(buf2,"value=%d",value);
            show_it = 1;
        }
    }
    else if (msg.isActiveSense())
    {
        // would have already been filtered out
        // if (!getPref8(PREF_MONITOR_ACTIVESENSE))
        s = "ActiveSense";
        show_it = 1;
    }

    // the following four are NOPs as they
    // don't set show_it

    else if (p0 == 0xF8)
    {
        s = "MIDI_CLOCK";
    }
    else if (p0 == 0xFA)
    {
        s = "MIDI CLOCK START";
    }
    else if (p0 == 0xFA)
    {
        s = "MIDI CLOCK CONTINUE";
    }
    else if (p0 == 0xFA)
    {
        s = "MIDI CLOCK STOP";
    }


    // CONTROL CHANGES

    else if (type == MIDI_TYPE_CC)  //  0x0b
    {
        s = "ControlChange";

        if (is_ftp)
        {
            if (p1 == FTP_NOTE_INFO)    // 0x1e
            {
                if (getPref8(PREF_MONITOR_FTP_NOTE_INFO))
                {
                    s = "NoteInfo";
                    uint8_t string = p2>>4;
                    uint8_t vel = p2 & 0x0f;
                    sprintf(buf2,"string=%d vel=%d",string,vel);
                    show_it = 1;
                }
            }

            else if ((p1 == FTP_SET_TUNING || p1 == FTP_TUNING))  // 0x1d || 0x3d
            {
                if (getPref8(PREF_MONITOR_FTP_TUNING_MSGS))
                {
                    if (p1 == FTP_SET_TUNING)   // 0x1D
                    {
                        s = "SetTuning";
                    }
                    else    // I am going to assume that if there is no tuning_note here, we inherit the most_recent_note, if any
                    {
                        s = "Tuning";
                    }

                    // 0x00 = -40,  0x40 == 0, 0x80 == +40
                    sprintf(buf2,"tuning=%d",p2);
                    show_it = 1;
                }
            }

            else if (p1 == FTP_COMMAND_OR_REPLY)
            {
                s = "ftpCmdOrReply";
                last_ftp_cmd[ msg.isOutput() ] = p2;

                bool known = true;
                const char *command_name = getFTPCommandName(p2);
                if (!command_name)
                {
                    command_name = "unknown";
                    known = false;
                }

                if (!known)
                    show_it = getPref8(PREF_MONITOR_UNKNOWN_FTP_COMMANDS);
                else if (p2 == FTP_CMD_POLY_MODE)
                    show_it = getPref8(PREF_MONITOR_FTP_POLY_MODE);
                else if (p2 == FTP_CMD_PITCHBEND_MODE)
                    show_it = getPref8(PREF_MONITOR_FTP_BEND_MODE);
                else if (p2 == FTP_CMD_VOLUME_LEVEL)
                    show_it = getPref8(PREF_MONITOR_FTP_VOLUME);
                else if (p2 == FTP_CMD_BATTERY_LEVEL)
                    show_it = getPref8(PREF_MONITOR_FTP_BATTERY);
                else if (p2 == FTP_CMD_GET_SENSITIVITY ||
                         p2 == FTP_CMD_SET_SENSITIVITY)
                    show_it = getPref8(PREF_MONITOR_FTP_SENSITIVITY);
                else
                    show_it = getPref8(PREF_MONITOR_KNOWN_FTP_COMMANDS);

                if (show_it)
                    sprintf(buf2,"%s",command_name);
            }

            else if (p1 == FTP_COMMAND_VALUE)
            {
                s = "ftpCommandParam";
                uint8_t command = last_ftp_cmd[ msg.isOutput() ];
                last_ftp_cmd[ msg.isOutput() ] = 0;

                bool known = true;
                const char *command_name = getFTPCommandName(command);
                if (!command_name)
                {
                    command_name = "unknown";
                    known = false;
                }

                if (!known)
                {
                    show_it = getPref8(PREF_MONITOR_UNKNOWN_FTP_COMMANDS);
                    if (show_it)
                        sprintf(buf2,"%s %02x",command_name,p2);
                }
                else if (command == FTP_CMD_POLY_MODE)
                {
                    show_it = getPref8(PREF_MONITOR_FTP_POLY_MODE);
                    if (show_it)
                        sprintf(buf2,"%s poly_mode=%02x",command_name,p2);
                }
                else if (command == FTP_CMD_PITCHBEND_MODE)
                {
                    show_it = getPref8(PREF_MONITOR_FTP_BEND_MODE);
                    if (show_it)
                        sprintf(buf2,"%s bend_mode=%02x",command_name,p2);
                }
                else if (command == FTP_CMD_VOLUME_LEVEL)
                {
                    show_it = getPref8(PREF_MONITOR_FTP_VOLUME);
                }
                else if (command == FTP_CMD_BATTERY_LEVEL) // we can parse this one because it doesn't require extra knowledge
                {
                    show_it = getPref8(PREF_MONITOR_FTP_BATTERY);
                    if (show_it)
                        sprintf(buf2,"%s battery_level=%02x",command_name,p2);
                }
                else if (command == FTP_CMD_GET_SENSITIVITY)
                {
                    show_it = getPref8(PREF_MONITOR_FTP_SENSITIVITY);
                    if (show_it)
                        sprintf(buf2,"%s string_sensitivity=%02x",command_name,p2);
                }
                else if (command == FTP_CMD_SET_SENSITIVITY)
                {
                    show_it = getPref8(PREF_MONITOR_FTP_SENSITIVITY);
                    if (show_it)
                    {
                        int string = p2 >> 4;
                        int level  = p2 & 0xf;
                        sprintf(buf2,"%s string_sensitivity[%d]=%d",command_name,string,level);
                    }
                }
                else if (command == FTP_CMD_DYNAMICS_SENSITIVITY)
                {
                    show_it = getPref8(PREF_MONITOR_KNOWN_FTP_COMMANDS);
                    if (show_it)
                        sprintf(buf2,"%s setting dynamic_sensitivity=%d",command_name,p2);
                }
                else if (command == FTP_CMD_DYNAMICS_OFFSET)
                {
                    show_it = getPref8(PREF_MONITOR_KNOWN_FTP_COMMANDS);
                    if (show_it)
                        sprintf(buf2,"%s setting dynamic_offset=%d",command_name,p2);
                }
                else if (command == FTP_CMD_TOUCH_SENSITIVITY)
                {
                    show_it = getPref8(PREF_MONITOR_KNOWN_FTP_COMMANDS);
                    if (show_it)
                        sprintf(buf2,"%s setting touch_sensitivity=%d",command_name,p2);
                }
                else
                {
                    show_it = show_it && getPref8(PREF_MONITOR_KNOWN_FTP_COMMANDS);
                }

            }   // is_ftp_port && it's an FTP command_value (0x1f)

            // any other CC's are considered "performance" CCs at this time ???
            // we at least try to get the "known" midi CC names

            else
            {
                sprintf(buf2,"%s(0x%02x)",getStandardCCName(p1),p2);
            }
        }   // is_ftp

        else
        {
            show_it = getPref8(PREF_MONITOR_EVERYTHING_ELSE);
            if (show_it)
            {
                if (port == MIDI_PORT_RPI)
                    getLooperCommandDescrip(buf2,p1,p2);
                else
                    sprintf(buf2,"%s(0x%02x)",getStandardCCName(p1),p2);
            }
        }

    }   // (type == MIDI_TYPE_CC)  //  0x0b)

    if (show_it)
    {
        char buf[200];
        sprintf(buf,"\033[%d;%dm%s(%d) chan(%d)  %02X  %-16s  %02x  %02x  %s",
            fg_color,
            bg_color,
            port_name,
            port_enum,
            msg.channel(),
            type,
            s,
            p1,
            p2,
            buf2);

        #if 1
            // fix for colors background colors wrapping
            strcat(buf,"\033[37;40m");
        #endif
            MONITOR_OUTPUT->println(buf);


    }   // show_it


}   // _monitor



// end of midiMonitor.cpp
