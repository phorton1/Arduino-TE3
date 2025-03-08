//------------------------------------------
// prefs.h
//------------------------------------------
// ideas for EEPROM Preferences for TE3
// gave up on this with alternative approach
// to try to port existing TE1 to TE3 as a
// rapid prototype.

#pragma once

#include "defines.h"


#define TEENSY_EXPRESSION3_PREF_VERSION   30
	// EEPROM location 0 is magic
	//
	// Although TE3 runs on a teensy4.1 and is generally
	// not compatible with TE1/2 on the teensy 3.6, we
	// carry forward the notion that the prefs themselves
	// can be versioned so that different versions can be
	// identified and an automatic factory reset done if
	// and when they change.
	//
	// The vesigial values were 237 for teensyExpression1
	// and 238 for teensyExpression2.


#define PREF_TYPE_UINT8			0
#define PREF_TYPE_UINT16		1
#define PREF_TYPE_ENUM			2
#define PREF_TYPE_STRING		3		// fixed maximum sized string
#define PREF_TYPE_PEDAL			4
#define PREF_TUPE_ROTARY		5
	// pedals and rotaries are handled specially


typedef struct {
	uint8_t		type;			// PREF_TYPE
	uint16_t 	offset;			// offset in EEPROM after the magic byte
	uint16_t	min;			// minimum value for UINT8 and UINT16 types (almost always zero); DEFAULT VALUE FOR ENUMS, minimum length for strings (force entry); unused for pedals
	uint16_t	max;			// maximum value for UINT8. UINT16, and ENUM types, maximum length of string; unused for pedals
	void 	   *def;			// default value fo UINT8 and UINT16 types, ptr to strings array for ENUMS, ptr to default string for strings, or pointer to pedalInfo_t
} prefDescriptor_t;


// prefs are enumerated here.
// certain ones are in repeating groups which are subsequently
// encapsulated into convenience methods.

//-------------------------------------------------------
// STREAMS
//-------------------------------------------------------
// OUTPUT: There are two potential output streams to the console,
// USB_SERIAL_PORT and DBG_SERIAL_PORT. It is envisioned
// that none, one, or both of these ports may be connected
// to the console.pm program (laptop) at any given time.
//
// INPUT: Serial input from the laptop can happen on
// either, both, or neither of those two streams.  That
// input takes the form of simple binary or unary TEXT commands,
// rPI_KERNEL binary_upload protocol, and/or the FILE_SYSTEM text
// protocol.
//
//------------------------------------------------------
// DEBUGGING AND MONITORING
//------------------------------------------------------
// There are a plethora of things that can be sent to
// the two output streams as colored text output.
//
//		- Debugging from TE3 itself (GREEN)
//      - Debugging from TE3_audio device (BLUE)
//		- Debugging from RPI:
//			- bootloader (CYAN)
//			- Looper (WHITE)
//      - Midi Monitoring per channel, message type,
//		  etc in a variety of colors
//
// All the debugging devices also have the ability to display
// RED and YELLOW (or some other color pair) error and warning
// messages.
//
//--------------------------------------------------------
// SANITY
//--------------------------------------------------------
// For sanity not all possible combinations will be implemented.
// There will be one main FOLLOW device that can be either
// "Off", or the USB or SERIAL (DBG) port.
//
// Then each category of output can either use the FOLLOW device,
// or be set specifically
//
//		FOLLOW 			- Off, USB, SERIAL
//		TE3_DEBUG 		- Off, USB, SERIAL, FOLLOW
//      TE3_AUDIO_DEBUG - Off, USB, SERIAL, FOLLOW
//		RPI_DEBUG		- Off, USB, SERIAL, FOLLOW
//		MIDI_MONITOR	- Off, USB, SERIAL, FOLLOW
//
// I think, for sanity, that there will only be one input
// device that will handle TEXT, rPi_KERNEL, and FILE_SYSTEM
// input.
//
//		SERIAL_INPUT	- Off, USB, SERIAL
//
// The defaults for these will evolve over time as the
// initial testing will likely be done on my desk using
// the USB port mostly, and then switch to the SERIAL port
// when I start putting the box on the floor and/or start
// predominantly using it with the iPad.


// Enumeration of FOLLOW_DEVICE

#define FOLLOW_DEVICE_OFF		0
#define FOLLOW_DEVICE_USB		1
#define FOLLOW_DEVICE_DBG	2

// Enumeration of devices that can follow the FOLLOW_DEVICE

#define SERIAL_DEVICE_OFF	    0
#define SERIAL_DEVICE_USB		1
#define SERIAL_DEVICE_DBG	2
#define SERIAL_DEVICE_FOLLOW	3		// follows the FOLLOW_DEVICE

// Enumeration of the serial input device

#define SERIAL_INPUT_OFF		0
#define SERIAL_INPUT_USB		1
#define SERIAL_INPUT_SERIAL		2


//---------------------------------------
// MIDI PORTS
//---------------------------------------
// It starts to get complicated here.
// There are upto four input and output USB Midi Ports.
// There is the MIDI_HOST input/output pair.
// There are two Serial Midi Ports: the RPI and the HUB (TE3_audio device).
//
// We *may* need to (quickly) route messages between these,
// 		particularly if we support the MIDI_HOST and/or FTP_SPOOFING.
//      but also because the SGTL5000 is now separate from the Looper
//		and the vestigial Looper code has sliders for the SGTL input
//		level and output volume.
// For sanity, we'd like to only use the 0th USB Midi input and output ports
//	   in the main TE3 implementation, noting that FTP spoofing and
//	   remote monitoring *may* require use of more than one USB port.
// I used to encapsulate the port (which is also variously called the "cable")
//  	in the general MIDI uint32_t as part of the 0'th nibble, with the channel
//		going into the 1st nibble.
// With the below enums I can tell you what port, and the direction, of any
//      midi message in the system.
// This scheme does not include enough information for a midi message to contain
//		its own "routing" information.  A midi-queue which also handles routing
//		will need extra information, and hence we might very well move the port/cable
//		completely out of the uint32_t "standard" usb midi message and into a
//		separate member variable (8 bytes per midi message?).


#define MIDI_PORT_ENUM_USB0		0
#define MIDI_PORT_ENUM_USB1		1
#define MIDI_PORT_ENUM_USB2		2
#define MIDI_PORT_ENUM_USB3		3
#define MIDI_PORT_ENUM_HOST		4
#define MIDI_PORT_ENUM_RPI		5		// Serial
#define MIDI_PORT_ENUM_HUB		6		// Serial

#define MIDI_PORT_BIT_USB0		0x0001
#define MIDI_PORT_BIT_USB1		0x0002
#define MIDI_PORT_BIT_USB2		0x0004
#define MIDI_PORT_BIT_USB3		0x0008
#define MIDI_PORT_BIT_HOST		0x0010
#define MIDI_PORT_BIT_RPI		0x0020		// Serial
#define MIDI_PORT_BIT_HUB		0x0040		// Serial
#define MIDI_PORT_BIT_OUTPUT	0x0080		// message is an output message


//---------------------------------------
// Pedal Configurations
//---------------------------------------
// Pedal configurations are special in that
// they are not handled as general preferences,
// but rather as a chunk of EEPROM locations
// with special accessors

#define MAX_PEDAL_NAME			4		// name of each pedal

#define NUM_PEDAL_CURVES		3		// number of curves per pedal
#define NUM_CURVE_POINTS		4		// number of points per curve

typedef struct
{
	uint8_t X;								// defaults depend on particular curve
	uint8_t Y;
}	pref_curve_point_t;

typedef struct
{
	pref_curve_point_t POINTS[NUM_CURVE_POINTS];
}	pref_curve_t;

typedef struct
{
	char			name[MAX_PEDAL_NAME+1]		// uppercase three or four letter name
	uint8_t			port;						// port/cable to send control messages to
	uint8_t			cc_num;						// the CC number associated with the pedal
	
	uint16_t		CALIB_MIN;				 	// 0..1023 - default(0)
	uint16_t		CALIB_MAX;               	// 0..1023 - default(1023)
	uint8_t     	CURVE_TYPE;              	// 0=linear, 1=asymptotic, 2=scurve - default(0=;inear)
	pref_curve_t 	CURVE[NUM_PEDAL_CURVES];
}	pref_pedal_t;



//--------------------------------------------------------
// LOOPER INPUT AND OUTPUT VOLUMES
//--------------------------------------------------------
// Although the THRU, LOOP, and MIX controls remain valid in TE3
// 		and will likely be controlled by rotaries/pedal as before,
//		the master INPUT and OUTPUT LEVEL sliders are now questionable.
//		Perhaps I will provice a pair of RCA jacks that connect to the
//		RevD audio shield Headphone jack, and thus could use the headphone
//		volume which *might* have more flexibility, at this time, I am
//		using the line_out level, which I've found needs to be set as
//		close to the maximum, without clipping, as possible, to get good
//		levels at the PA.  And, although I never plan on using the RevD
//		microphone input and pre-amp, I am totally relying on the guitar
//		having a pre-amp that delivers line-level outputs to the guitar
//		jack, and likewise have more-or-less maximized the LINE_IN level
//		to get it to sound good at the PA.
// Therefore, the presence, and possible support, of sliders in the
//		Looper UI for the master input and output levels is questionable
//		at this time. They are currently disconnected by the LOOPER3 define.
// I am *tempted* to have a section of prefs related to setting up the SGTL
//		which could override the default and preferred settings in TE3_audio,
//		but I think I need to add that (much) later as necessary and feel
//		a compulsion to get SOMETHING working in short order.
// Hence, those two rotaries will not be initially hooked up.
// Furthermore, with the addition of the rotary buttons, I sort of
//	    envision using at least one of the rotaries to enable the
//		entry of strings (and/or the ability to make one or both of
//		of the touch screens into a "keyboard").
//		In that vein I suspect that I REALLY DONT WANT to mess with
//		the looper UI but I also envision making the Looper able to
//		save, restore, delete, rename, records CLIPSETS, and sort
//		of see that being accomplished by turning the TE3 touchscreen
//		into a keyboard that works with the Looper in that regards.


// I guess a lot of this is borderline confusion about trying to make
// the old TE1 "sort-of" general purpose.  Things like the PATCH_LIST
// on the synthesizer, and how they are selected, etc (not to mention
// multi-mode on the FTP).






//====================================
// the main prefs_t data structure
//====================================

typedef struct
{
	uint8_t 		BRIGHTNESS;					// LED brightness, 1..100 - default=30
	uint8_t			DEBUG_DEVICE;         		// off, USB, Serial - default(2=Serial)
	uint8_t			FILE_SYS_DEVICE;   			// off, Debug, USB, Serial - default(1=Debug)
	uint8_t			SPOOF_FTP;         			// off, on - on implies FTP_PORT == HOST
	uint8_t			FTP_PORT;         			// off, USB, HOST

	char			RIG_NAME[MAX_RIG_NAME + 1];

	pref_pedal_t 	PEDAL[NUM_PEDALS];

	// midi monitoring, general on/off

	uint8_t			MIDI_MONITOR;    			// off, Debug, USB, Serial - default(off)

	// whether to monitor specific ports
	// these are turned into 7 bit masks for matching the ports in enqueMidi

	uint8_t			MONITOR_INPUT[NUM_MIDI_PORTS];
	uint8_t			MONITOR_OUTPUT[NUM_MIDI_PORTS];

	// what channels to monitor on any monitored ports

	uint16_t 		MONITOR_CHANNEL[MIDI_MAX_CHANNEL];		// off, on - default(on) for 16 channels

	// what to monitor on any monitored ports and channels

	uint8_t			MONITOR_SYSEX;          	// off, on, Detail - default(on)
	uint8_t			MONITOR_ACTIVE_SENSE;    	// off, on - default(off)
	uint8_t			MONITOR_NOTE_ON;        	// off, on - default(off)
	uint8_t			MONITOR_NOTE_OFF;       	// off, on - default(off)
	uint8_t			MONITOR_VELOCITY;       	// off, on - default(off)   note: "after touch poly"
	uint8_t			MONITOR_PROGRAM_CHG;    	// off, on - default(on)
	uint8_t			MONITOR_AFTER_TOUCH;     	// off, on - default(off)
	uint8_t			MONITOR_PITCH_BEND;      	// off, on - default(off)
	uint8_t 		MONITOR_CCS;            	// off, on - default(off)
	uint8_t			MONITOR_EVERYTHING_ELSE;	// off, on - default(off)

	// FTP specific monitoring only occurs on the designated FTP input and output port
	// REGARDLESS of whether port/channel is specifically allowed.  Note that
	// identified FTP patches are in Addition to the SYSEX that might
	// be monitoried on that port/channel.

	uint8_t			MONITOR_FTP;                	// off, on - default(off)
	uint8_t			MONITOR_FTP_PATCHES;  			// off, on - default(off)
	uint8_t			MONITOR_FTP_NOTE_INFO;     	    // off, on - default(off)
	uint8_t			MONITOR_FTP_TUNING_MSGS;    	// off, on - default(off)
	uint8_t			MONITOR_FTP_COMMANDS;       	// off, on - default(off)
	uint8_t			MONITOR_FTP_VALUES;         	// off, on - default(off)
	uint8_t			MONITOR_FTP_POLY_MODE;     	    // off, on - default(off)
	uint8_t			MONITOR_FTP_BEND_MODE;      	// off, on - default(off)
	uint8_t			MONITOR_FTP_VOLUME;         	// off, on - default(off)
	uint8_t			MONITOR_FTP_BATTERY;        	// off, on - default(off)
	uint8_t			MONITOR_FTP_SENSITIVITY;    	// off, on - default(off)
	uint8_t			MONITOR_FTP_KNOWN_COMMANDS;     // off, on - default(off)
	uint8_t			MONITOR_FTP_UNKNOWN_COMMANDS;   // off, on - default(off)



}	prefs_t;




//================================================
// API
//================================================

extern prefs_t prefs;
	// global public direct read/write access

// initialize and reset methods

extern void reset_prefs();
	// clears the EEPROM but does not re-read prefs
	// you will typically need to call read_prefs() or reboot
	// after this.
extern bool read_prefs();
	// returns true if prefs were automatically reset
extern void save_prefs();


// Offset based accessors used by config system.
// These methods know the type of the pref and take, or return,
// a uint8_t, uint16_t, or const char * as the uint32_t parameter
// or uint32_t return type. Min and Maxes are returned as uint16_t's.
// There is no range checking in these routines!

#define pcast(m)			((uint32_t) &(m))
#define poff(PREF)			((uint16_t) {pcast(prefs.PREF) - pcast(prefs)})

extern void 	setPref(uint16_t off, uint32_t value, const char *name = 0);
extern uint32_t getPref(uint16_t off, const char *name = 0);
extern uint16_t getPrefMin(uint16_t off);
extern uint16_t getPrefMax(uint16_t off);
extern bool 	prefs_dirty();



// end of prefs.h
