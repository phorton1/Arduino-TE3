//----------------------------------------------
// midiQueue.cpp
//----------------------------------------------
// Currently most of this file is dedicated to FTP handling,
// with only a few routines otherwise used to send immediate
// midi messages.


#include "myDebug.h"
#include "midiQueue.h"
#include "prefs.h"
#include "ftp.h"
#include "ftp_defs.h"
#include "midiHost.h"
#include "expSystem.h"


#define DEBUG_MIDI_SEND     1       // show sent midi messages

#define DEBUG_FTP_QUEUE     1       // show incoming ftp enqueue & dequeue
#define DEBUG_FTP_PROC      2       // show ftp dequeue processing; 2 shows header
#define DEBUG_FTP_NOTES     1       // separate define for ftp note details
#define DEBUG_FTP_COMMANDS  1       // show FTP command processing


#define MAX_FTP_IN_QUEUE    1024     // plenty big enough in testing
#define MAX_FTP_OUT_QUEUE   1024
#define FTP_RETRY_TIME		100
#define FTP_RETRY_COUNT		10


#define MAX_SYSEX       1024

//---------------------------------------
// FTP vars
//---------------------------------------
// starting with globally used FTP_ACTIVE_PORT

int FTP_ACTIVE_PORT = -1;

// The FTP in/out queues

static volatile int ftp_in_head;
static volatile int ftp_in_tail;
static uint32_t ftp_in_queue[MAX_FTP_IN_QUEUE];

static volatile int ftp_out_head;
static volatile int ftp_out_tail;
static uint16_t ftp_out_queue[MAX_FTP_OUT_QUEUE];

// Variables for handling two part FTP COMMAND and REPLY sequences

static int      ftp_command_count = 0;          // end to end protection of full sendFTPCommandAndValue() reply handling
static uint8_t  pending_ftp_command;            // the most recently dequeued outgoing FTP command that is being sent
static uint8_t  pending_ftp_command_value;      // the most recently dequeued outgoing FTP command value that is being sent
static int 		ftp_command_retry_count;        // number of times we have tried resending while waiting for a reply
static uint32_t ftp_command_time;               // time we sent the last command-value pair to the FTP

// Variables for handling FTP notes

static uint8_t most_recent_note_val = 0;
static uint8_t most_recent_note_vel = 0;
    // these values are cached from the most recent NoteOn/NoteOff
    // messages and used to create (or delete) my note_t's in ftp.cpp
	// upon subsequent NoteInfo messages.


//============================================================
// sendMidiMessage and variants
//============================================================

static void sendMidiMessage(const char *what, uint8_t port, uint8_t type, uint8_t channel, uint8_t p1, uint8_t p2)
{
    if (channel < 1 || channel > 16)
    {
        my_error("sendMidiMessage(%s) channel(%d) must be between 1 and 16",what,channel);
        return;
    }

	// we first create a msgUnion to actually send to the correct port (cable) of the 4 devices

	uint8_t use_port =
		(port <= MIDI_PORT_USB4) ? port :
		(port <= MIDI_PORT_HOST2) ? port - MIDI_PORT_HOST1 : 0;

	msgUnion msg(use_port, type, channel, p1, p2);

    if (port <= MIDI_PORT_USB4)
	{
        #if DEBUG_MIDI_SEND
            display_level(0,4,"sendMidiMessageUSB(%s, 0x%02x,  0x%02x,0x%02x,0x%02x,0x%02x) = 0x%08x use_port=0x%02x",what,port,type,channel,p1,p2,msg.i,use_port);
		#endif
        usb_midi_write_packed(msg.i);
		usb_midi_flush_output();
        theSystem.midiActivity(ACTIVITY_INDICATOR_USB_OUT);
 	}
	else if (port <= MIDI_PORT_HOST2)
	{
        #if DEBUG_MIDI_SEND
            display_level(0,4,"sendMidiMessageHost(%s, 0x%02x,  0x%02x,0x%02x,0x%02x,0x%02x) = 0x%08x use_port=0x%02x",what,port,type,channel,p1,p2,msg.i,use_port);
		#endif
        midi_host.write_packed(msg.i);
        theSystem.midiActivity(ACTIVITY_INDICATOR_HOST_OUT);
	}
	else if (port == MIDI_PORT_RPI)
    {
        #if DEBUG_MIDI_SEND
            display_level(0,4,"sendMidiMessageRPI(%s, 0x%02x,  0x%02x,0x%02x,0x%02x,0x%02x) = 0x%08x use_port=0x%02x",what,port,type,channel,p1,p2,msg.i,use_port);
        #endif
	    RPI_SERIAL_PORT.write(msg.b,4);
        theSystem.midiActivity(ACTIVITY_INDICATOR_RPI_OUT);
	}
	else if (port == MIDI_PORT_HUB)
    {
        #if DEBUG_MIDI_SEND
            display_level(0,4,"sendMidiMessageHUB(%s, 0x%02x,  0x%02x,0x%02x,0x%02x,0x%02x) = 0x%08x use_port=0x%02x",what,port,type,channel,p1,p2,msg.i,use_port);
        #endif
	    HUB_SERIAL_PORT.write(msg.b,4);
        theSystem.midiActivity(ACTIVITY_INDICATOR_HUB_OUT);
	}
    else
    {
        my_error("Uknown PORT(0x%02x) in sendMidiMessage(%s, 0x%02x,  0x%02x,0x%02x,0x%02x,0x%02x) = 0x%08x use_port=0x%02x",port,what,port,type,channel,p1,p2,msg.i,use_port);
        return;
    }

	// We would then then we set our port into the msg, and pass it to
	// enqueueMidiMonitor as output for monitoring display

	// msg.setOutput();
	// msg.setPort(port);
	// enqueueMidi(msg);
}


void sendMidiProgramChange(uint8_t port, uint8_t channel, uint8_t prog_num)
{
    sendMidiMessage("programChange", port, MIDI_TYPE_PGM_CHG, channel, prog_num, 0);	// 0x0c
}

void sendMidiControlChange(uint8_t port, uint8_t channel, uint8_t cc_num, uint8_t value)
{
    sendMidiMessage("controlChange", port, MIDI_TYPE_CC, channel, cc_num, value);	// 0x0b
}



//============================================================
// The rest of this file is currently FTP stuff
//============================================================

extern void setFTPActivePort()
    // Called after prefs loaded in TE3.ino, or when value of PREF_FTP_PORT
    // changes in configSystem.  Note that it is not called when SPOOF_FTP
    // changes, as this causes a system rebooot.
{
    int ftp_pref = getPref8(PREF_FTP_PORT);
    int use_port = 0;
    if (getPref8(PREF_SPOOF_FTP) || ftp_pref == FTP_PORT_HOST)
        use_port = MIDI_PORT_HOST1;
    else if (ftp_pref == FTP_PORT_REMOTE)
        use_port = MIDI_PORT_USB1;

    display(0,"setFTPActivePort(0x%02x)",use_port);
    FTP_ACTIVE_PORT = use_port ? use_port : -1;
}


//------------------------------------------------
// FTPIn queue
//------------------------------------------------

static void _handleFTPIn(uint32_t msg32);
    // forward


void enqueueFTPIn(int port, uint32_t msg32)
    // from theSystem::critical_timer_handler() for usb or
    // midiHost::rx_data() for host, quickly enqueues FTP messages
    // for further processing.  The port is only used for debugging output.
{
    #if DEBUG_FTP_QUEUE
        display_level(0,1,"enqueueFTPIn port(0x%02x) msg(0x%08x) head(%d) tail(%d)",port,msg32,ftp_in_head,ftp_in_tail);
    #endif

    // stuff the port nibble into the message

    msg32 &= ~MIDI_PORT_NUM_MASK;
    msg32 |= port;

    __disable_irq();
    ftp_in_queue[ftp_in_head++] = msg32;
    if (ftp_in_head == MAX_FTP_IN_QUEUE)
        ftp_in_head = 0;
    if (ftp_in_head == ftp_in_tail)
        my_error("enqueueFTPIn() overflow at %d",ftp_in_head);
    __enable_irq();

    #if 0   // DEBUG_FTP_QUEUE
        warning(0,"enqueueFTPIn returning head(%d)",ftp_in_head);
    #endif
}


void dequeueFTPIn()
{
    // while (queue_tail != queue_head)
    if (ftp_in_tail != ftp_in_head)
    {
        #if DEBUG_FTP_QUEUE
			display_level(0,2,"dequeueFTPIn(0x%08x) head(%d) tail(%d)",
				ftp_in_queue[ftp_in_tail],
				ftp_in_head,
				ftp_in_tail);
        #endif

		__disable_irq();
        uint32_t msg32 = ftp_in_queue[ftp_in_tail++];
        if (ftp_in_tail == MAX_FTP_IN_QUEUE)
            ftp_in_tail = 0;
		__enable_irq();

        _handleFTPIn(msg32);
	}
}



//--------------------------------------------------------------
// FTP In Processing (_handleFTPIn and dequeueFTPIn)
//--------------------------------------------------------------

static void _handleFTPIn(uint32_t msg32)
    // Handles FTPIn messages that we recognize and need.
    // Skip handling of anything else, like SYSEX, PITCHBEND, and so on
{
    msgUnion msg(msg32);

    static uint8_t  ftp_in_command_in_process;
        // holds the command portion for a 2 part
        // command-value reply

	uint8_t type = msg.type();
	uint8_t p1 = msg.param1();
	uint8_t p2 = msg.param2();

	#if DEBUG_FTP_PROC > 1
		display_level(0,3,"_handleFTPIn  (0x%08x) port(0x%02x) channel(%-2d) type(0x%02x) param1(0x%02x) param2(0x%02x)",
			msg.i,
			msg.port(),
            msg.channel(),
			type,
			p1,
			p2);
    #endif

	if (type == MIDI_TYPE_NOTE_OFF || type == MIDI_TYPE_NOTE_ON)	// 0x08 or 0x09
	{
        #if DEBUG_FTP_NOTES
            display_level(0,5,"FTP most_recent_note val=%-3d vel=%d",p1,p2);
		#endif
        most_recent_note_val = p1;
		most_recent_note_vel = p2;
	}
	else if (type == MIDI_TYPE_CC)				// 0x0b = Control Change
    {
		if (p1 == FTP_NOTE_INFO)    // 0x1e
		{
			// note that we keep calling addNote and deleteNote
			// even when we are not in tuner mode, which theoretically
			// might slow host mode down a bit ... we *could* make the
			// add a midiQueue::setFTPTunerMode(bool) to only add and
			// delete notes when we are actually in the tuner.

			uint8_t string = p2>>4;
			uint8_t vel = p2 & 0x0f;
			if (most_recent_note_vel)
			{
                #if DEBUG_FTP_NOTES
                    display_level(0,5,"FTP addNote(%d,%d,%d,%d)",most_recent_note_val,most_recent_note_vel,string,vel);
                #endif
				addNote(most_recent_note_val,most_recent_note_vel,string,vel);
			}
			else
			{
                #if DEBUG_FTP_NOTES
                    display_level(0,5,"FTP deleteNote(%d)",string);
                #endif
				deleteNote(string);
			}
			most_recent_note_vel = 0;
			most_recent_note_val = 0;
		}
		else if (p1 == FTP_SET_TUNING || p1 == FTP_TUNING)  // 0x1d || 0x3d
		{
			if (p1 == FTP_SET_TUNING)   // 0x1D
			{
                #if DEBUG_FTP_NOTES
                    display_level(0,5,"FTP tuning_note1 = ftp_cur_note",0);
                #endif
				ftp_tuning_note = ftp_cur_note;
			}
			else if (!ftp_tuning_note)
			{
                #if DEBUG_FTP_NOTES
                    display_level(0,5,"FTP tuning_note2 = ftp_cur_note",0);
                #endif
				ftp_tuning_note = ftp_cur_note;
			}

			// 0x00 = -40,  0x40 == 0, 0x80 == +40
			int tuning = ((int) p2) - 0x40;      // 40 == 0,  0==-
			if (ftp_tuning_note)
			{
                #if DEBUG_FTP_NOTES
                    display_level(0,5,"FTP ftp_tuning_note->tuning = %d",tuning);
                #endif
				ftp_tuning_note->tuning = tuning;
			}
		}

		else if (p1 == FTP_COMMAND_OR_REPLY)
		{
            #if DEBUG_FTP_PROC > 1
                display_level(0,4,"FTP ftp_in_command_in_process=0x%02x",p2);
            #endif
            
			ftp_in_command_in_process = p2;
		}
		else if  (p1 == FTP_COMMAND_VALUE)
		{
			uint8_t command = ftp_in_command_in_process;
			ftp_in_command_in_process = 0;

			if (command == FTP_CMD_POLY_MODE)
			{
                #if DEBUG_FTP_PROC
                    display_level(0,4,"FTP poly_mode = 0x%02x",p2);
                #endif
				ftp_poly_mode = p2;
			}
			else if (command == FTP_CMD_PITCHBEND_MODE)
			{
                #if DEBUG_FTP_PROC
                    display_level(0,4,"FTP bend_mode = 0x%02x",p2);
                #endif
				ftp_bend_mode = p2;
			}
			else if (command == FTP_CMD_BATTERY_LEVEL) // we can parse this one because it doesn't require extra knowledge
			{
                #if DEBUG_FTP_PROC
    				display_level(0,4,"FTP battery_level = 0x%02x",p2);
                #endif
                ftp_battery_level = p2;
			}
			else if (command == FTP_CMD_GET_SENSITIVITY)
			{
				// we double check that this is a response to our
				// specific pending command !?!
				if (pending_ftp_command == FTP_CMD_GET_SENSITIVITY)
				{
                    #if DEBUG_FTP_PROC
                    	display_level(0,4,"FTP sensitivity[%d] = 0x%02x",pending_ftp_command_value,p2);
					#endif
                    ftp_sensitivity[pending_ftp_command_value] = p2;
				}
			}
			else if (command == FTP_CMD_SET_SENSITIVITY)  // we can parse this one because it doesn't require extra knowledge
			{
				int string = p2 >> 4;
				int level  = p2 & 0xf;
                #if DEBUG_FTP_PROC
                    display_level(0,4,"FTP sensitivity2[%d] = 0x%02x",string,level);
				#endif
                ftp_sensitivity[string] = level;
			}
			else if (command == FTP_CMD_DYNAMICS_SENSITIVITY)
			{
                #if DEBUG_FTP_PROC
    				display_level(0,4,"FTP dynamic_range = 0x%02x",p2);
				#endif
                ftp_dynamic_range = p2;
			}
			else if (command == FTP_CMD_DYNAMICS_OFFSET)
			{
                #if DEBUG_FTP_PROC
    				display_level(0,4,"FTP dynamic_offset = 0x%02x",p2);
				#endif
                ftp_dynamic_offset = p2;
			}
			else if (command == FTP_CMD_TOUCH_SENSITIVITY)
			{
                #if DEBUG_FTP_PROC
    				display_level(0,4,"FTP touch_sensitivity = 0x%02x",p2);
				#endif
                ftp_touch_sensitivity = p2;
			}

			// now that we have the 2nd 3F message, if we matched the 1F message,
			// clear the pending outgoing command

			if (command == pending_ftp_command)
			{
                #if DEBUG_FTP_COMMAND
                    display_level(0,4,"FTP clearing pending_ftp_command(0x%02x) count(%d)",pending_ftp_command,ftp_command_count);
				#endif
                pending_ftp_command = 0;
                ftp_command_count--;

			}

		}	// p1 == FTP_COMMAND_VALUE
	}	// type == 0x0b   Control Change


}	// handleFTP()



//================================================
// FTP Out Command/Reply Processing
//================================================

// extern
bool pendingFTPCount()
{
    return ftp_command_count;
}


void sendFTPCommandAndValue(uint8_t cmd, uint8_t val)
	// merely enquees the 16 bit command and value
{
	if (FTP_ACTIVE_PORT == -1)
	{
		warning(0,"FTP port not active in sendFTPCommandAndValue(0x%02x,0x%02x)",cmd,val);
		return;
	}

    ftp_command_count++;

    #if DEBUG_FTP_COMMANDS
        display_level(0,2,"sendFTPCommandAndValue(0x%02x,0x%02x) command_count(%d)",cmd,val,ftp_command_count);
    #endif

	uint16_t cmd_and_val = (cmd << 8) | val;

    // __disable_irq();
    ftp_out_queue[ftp_out_head++] = cmd_and_val;
    if (ftp_out_head == MAX_FTP_OUT_QUEUE)
        ftp_out_head = 0;
    if (ftp_out_head == ftp_out_tail)
        my_error("ftp_out_queue overflow at %d",ftp_out_head);
    // __enable_irq();
}


static uint16_t _dequeueOutgoing()
{
    uint16_t cmd_and_val = 0;
    if (ftp_out_tail != ftp_out_head)
    {
        cmd_and_val = ftp_out_queue[ftp_out_tail++];
        if (ftp_out_tail == MAX_FTP_OUT_QUEUE)
            ftp_out_tail = 0;
    }
    return cmd_and_val;
}


static void _sendPendingFTPCommand()
{
    if (FTP_ACTIVE_PORT != -1)      // FTP PORT IS ACTIVE
    {
		sendMidiControlChange(FTP_ACTIVE_PORT, FTP_CONTROL_CHANNEL, FTP_COMMAND_OR_REPLY, pending_ftp_command);
		sendMidiControlChange(FTP_ACTIVE_PORT, FTP_CONTROL_CHANNEL, FTP_COMMAND_VALUE,    pending_ftp_command_value);
	}
    ftp_command_time = millis();
}



void processOutgoingFTPCommands()
{
    // see if there's a command to dequue and send
    // dequeue them even if we don't send them

    if (!pending_ftp_command)
    {
		uint16_t cmd_and_val = _dequeueOutgoing();
        if (cmd_and_val)
        {
			pending_ftp_command = cmd_and_val >> 8;
            pending_ftp_command_value = cmd_and_val & 0xff;
            #if DEBUG_FTP_COMMANDS
                display_level(0,3,"FTP start pending_ftp_cmd(0x%02x) val(0x%02x)",pending_ftp_command,pending_ftp_command_value);
            #endif
            ftp_command_retry_count = 0;
            _sendPendingFTPCommand();
        }
    }
    else if (ftp_command_retry_count > FTP_RETRY_COUNT)
    {
        my_error("FTP timed out sending cmd(0x%02x) val(0x%02x)",pending_ftp_command,pending_ftp_command_value);
        ftp_command_retry_count = 0;
        pending_ftp_command = 0;
        ftp_command_count--;
    }
    else if (millis() - ftp_command_time > FTP_RETRY_TIME)
    {
        ftp_command_retry_count++;
        #if DEBUG_FTP_COMMANDS
            display_level(0,3,"FTP resend(%d) cmd(0x%02x) val(0x%02x)",ftp_command_retry_count,pending_ftp_command,pending_ftp_command_value);
        #endif
        _sendPendingFTPCommand();
    }
}



