//----------------------------------------------
// midiQueue.h
//----------------------------------------------
#pragma once

#include "defines.h"
#include "prefs.h"


#define MIDI_OUTPUT_B2_FLAG  0x80
    // set into the high order bit of the B2 byte

class msgUnion
    // USB raw input ports map to mine, but HOST0,1
    // are 4,5 in my scheme and SERIAL0 is 6,  The OUTPUT
    // state is weirdly stored in the high order bit
    // of the 3rd byte, b[2], param1.
{
    public:

		msgUnion(uint32_t msg32)  { i = msg32; }

        msgUnion(uint8_t port, uint32_t msg32)
        {
            i = (msg32 & ~MIDI_PORT_NUM_MASK) | port;
        }
        msgUnion(uint8_t port, uint8_t type, uint8_t channel, uint8_t p1, uint8_t p2)
        {
            b[0] = type | port;
            b[1] = (type<<4) | (channel - 1);
            b[2] = p1;
            b[3] = p2;
        }
		void setPort(uint8_t port)
		{
            i = (i & ~MIDI_PORT_NUM_MASK) | port;
		}
        void setOutput()
        {
            b[2] |= MIDI_OUTPUT_B2_FLAG;
        }

        inline uint8_t port()		const { return i & MIDI_PORT_NUM_MASK; }
		inline bool    isUSB()		const { return port() <= MIDI_PORT_USB4; }
        inline bool    isHost()		const { return port() >= MIDI_PORT_HOST1 && port() <= MIDI_PORT_HOST2; }
        inline bool    isSerial()	const { return port() >= MIDI_PORT_RPI && port() <= MIDI_PORT_HUB; }
        inline bool    isRPI()		const { return port() == MIDI_PORT_RPI; }
        inline bool    isHUB()		const { return port() == MIDI_PORT_HUB; }

        inline bool    isOutput()	const { return b[2] & MIDI_OUTPUT_B2_FLAG; }

        inline uint8_t portEnum()	const { return (i & MIDI_PORT_NUM_MASK) >> 4; }

        inline uint8_t type()   	const { return i & 0x0f; }
        inline uint8_t channel()	const { return (b[1] & 0xf) + 1; }
        inline uint8_t param1() 	const { return b[2] & ~MIDI_OUTPUT_B2_FLAG; }
        inline uint8_t param2() 	const { return b[3]; }

        bool isActiveSense()		const { return (i & 0xff0f) == 0xfe0f; }

		inline uint8_t activityIndex() const
		{
			int p = port();
			bool o = isOutput();
            if (p <= MIDI_PORT_USB3)
            {
				return o ? ACTIVITY_INDICATOR_USB_OUT :
						   ACTIVITY_INDICATOR_USB_IN;
            }
            else if (p <= MIDI_PORT_HOST2)
            {
                return o ? ACTIVITY_INDICATOR_HOST_OUT :
						   ACTIVITY_INDICATOR_HOST_IN;
            }
            else if (p == MIDI_PORT_RPI)
            {
				return o ? ACTIVITY_INDICATOR_RPI_OUT :
						   ACTIVITY_INDICATOR_RPI_IN;
            }
            else // p == MIDI_PORT_HUB
            {
                return o ? ACTIVITY_INDICATOR_HUB_OUT :
						   ACTIVITY_INDICATOR_HUB_IN;
            }


			#if 0	// OLD
				return p <= MIDI_PORT_USB3 ?
					o ? ACTIVITY_INDICATOR_USB_OUT :
						ACTIVITY_INDICATOR_USB_IN :
				p <= MIDI_PORT_HOST2 ?
					o ? ACTIVITY_INDICATOR_HOST_OUT :
						ACTIVITY_INDICATOR_HOST_IN :
				o ? ACTIVITY_INDICATOR_SERIAL_OUT :
					ACTIVITY_INDICATOR_SERIAL_IN;
			#endif
		}

	// data

    union {
        uint32_t i;
        uint8_t b[4];
    };
};


//-------------------------------------
// generic sendMidi() methods
//-------------------------------------

// extern void sendMidiSysex(uint8_t port, int length, const uint8_t *buf);
extern void sendMidiProgramChange(uint8_t port, uint8_t channel, uint8_t prog_num);
extern void sendMidiControlChange(uint8_t port, uint8_t channel, uint8_t cc_num, uint8_t value);



//=====================================
// The rest is currently FTP only
//=====================================

extern int FTP_ACTIVE_PORT;
    // Port to which FTP commands will be sent, and which will be monitored
    // for FTP information. Based on PREF_FTP_PORT and PREF_SPOOF_FTP.
    //
    //      Off => -1
    //      Host | PREF_SPOOF_FTP => MIDI_PORT_HOST1
    //      Remote => MIDI_PORT_USB1

extern void setFTPActivePort();
    // Called after prefs loaded in TE3.ino, or when value of PREF_FTP_PORT
    // changes in configSystem.  Note that it is not called when SPOOF_FTP
    // changes, as this causes a system reboot.


extern void enqueueFTPIn(int port, uint32_t msg32);
    // enqueue incoming messages from USB (critical_timer_handler())
    // or MIDI_HOST (interrupt) for processing from timer_handler()
extern void dequeueFTPIn();
    // dequeue FTP messages from slower timer_handler() and process
    // them for information and/or pending commands.

extern void sendFTPCommandAndValue(uint8_t cmd, uint8_t val);
    // enqueue an outgoing FTP CommandAndValue for
    // reply processing and retries
extern bool pendingFTPCount();
    // used to serialize multiple successive FTP commands
    // withouit overlaps
extern void processOutgoingFTPCommands();
    // handle the outgoing FTP command queue by either
    // sending a new command, waiting for a reply
    // or doing a retry
    

// end of midiQueue.h