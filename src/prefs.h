//-------------------------------
// prefs.h
//-------------------------------

#pragma once

#include "defines.h"

#define TEENSY_EXPRESSION3_PREF_VERSION   30

#define PREF_NONE               -1


//-------------------------------------------------
// TEXT OUTPUT STREAMS
//-------------------------------------------------
// There are two potential output streams to the console,
// USB_SERIAL_PORT and DBG_SERIAL_PORT. It is envisioned
// that none, one, or both of these ports may be connected
// to the console.pm program (laptop) at any given time.
//
// Then there are a plethora of things that can be sent to
// the two output streams as colored text output.
//
//		- Debugging from TE3 itself (GREEN)
//      - Debugging from TE3_audio device - referred to as HUB - (BLUE)
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
// For sanity not all possible combinations will be implemented.
// There is one FOLLOW_DEVICE that can be either "Off",
// or the USB or SERIAL (DBG) port.
//
//		FOLLOW 			- Off, USB, SERIAL
//
// Then each category of output can either use the FOLLOW device,
// or be set specifically:
//
//		TE3_DEBUG 		- Off, USB, SERIAL, FOLLOW
//      HUB_DEBUG 		- Off, USB, SERIAL, FOLLOW
//		RPI_DEBUG		- Off, USB, SERIAL, FOLLOW
//		MONITOR_OUTPUT	- Off, USB, SERIAL, FOLLOW
//
//-----------------------------------------------------------
// INPUT STREAM
//-----------------------------------------------------------
// The TE3_DEBUG Stream is generally used for input from
// the console to the system.  This serial port does not
// expect serial MIDI messages, but does expect:
//
//		- line oriented TEXT_COMMANDS
//		  that work directly on TE3 (REBOOT, RESET, etc)
//		  that are converted to serial midi to the HUB (REBOOT_AUDIO, DUMP_AUDIO, DUMP_SGTL, etc)
//        that can reboot the rPi (reboot_rpi)
//      - rPi kernel BINARY_UPLOAD protocol bracketed by ctrl-E (chr(5))
//      - FILE_SYSTEM text protocol bracketed by ctrl-A (chr(1))
//
// I used to differentiate a port for the FILE_SYSTEM, but as of TE3, it is
// now always synonymous with the TE3_DEBUG stream.
// NOTE that even though the TPI_DEBUG output can be routed
// differently than the TE3_DEBUG port, the kernel BINARY_UPLOAD
// always takes place through the TE3_DEBUG port.


// Enumeration of FOLLOW_DEVICE

#define FOLLOW_DEVICE_OFF		0
#define FOLLOW_DEVICE_USB		1	// the teensy USB port
#define FOLLOW_DEVICE_DBG		2	// the TE3 serial port plug on back panel

// Enumeration for devices that can follow the FOLLOW_DEVICE

#define SERIAL_DEVICE_OFF	    0
#define SERIAL_DEVICE_USB		1
#define SERIAL_DEVICE_DBG		2
#define SERIAL_DEVICE_FOLLOW	3		// follows the FOLLOW_DEVICE

// values for PREF_FTP_PORT

#define FTP_PORT_OFF            0
#define FTP_PORT_HOST           1
#define FTP_PORT_REMOTE         2



//--------------------------------------------------------------------------------
// SETTINGS (PREFERENCES) OPTIONS
//--------------------------------------------------------------------------------
// EEPROM location 0 is magic
// 		it is a version number for the EEPROM itself so that
//      we can automatically do a factory reset when the layout
//		of the preferences change.
// These defines are the locations in EEPROM of these items

#define PREF_VERSION			0			// magic version number


#define PREF_BRIGHTNESS         1           // 1..100 - default(40)

#define PREF_FOLLOW_DEVICE      2           // off, USB, SERIAL - default(USB)
#define PREF_TE3_DEBUG_STREAM 	3			// off, USB, SERIAL, FOLLOW - default(FOLLOW)
#define PREF_HUB_DEBUG_OUTPUT	4			// off, USB, SERIAL, FOLLOW - default(FOLLOW)
#define PREF_RPI_DEBUG_OUTPUT	5			// off, USB, SERIAL, FOLLOW - default(FOLLOW)

#define PREF_SPOOF_FTP          6           // off, on - default(off)
#define PREF_FTP_PORT           7           // off, Host, Remote, default(Off)

#define FTP_OUTPUT_PORT    (getPref8(PREF_SPOOF_FTP) ? 1 : getPref8(PREF_FTP_PORT))


//--------------------------------
// pedals
//--------------------------------

#define PREF_PEDAL0    (PREF_FTP_PORT + 1)      // skip a byte from header

#define MAX_PEDAL_CURVES                3       // number of curves per pedal
#define MAX_CURVE_POINTS                4       // number of points per curve
#define MAX_PEDAL_CURVE_POINTS          (MAX_PEDAL_CURVES * MAX_CURVE_POINTS)

#define PEDAL_MODE_NORMAL               0x00
#define PEDAL_MODE_SERIAL               0x01
    // a Pedal can send it's data via USB to the iPad, or over the Serial port to the rPi.

#define PREF_PEDAL_MODE_OFFSET          0		// the pedal mode is "normal" or "serial"
#define PREF_PEDAL_CURVE_TYPE_OFFSET    1       // 0=linear, 1=asymptotic, 2=scurve - default(0) == num_points
#define PREF_PEDAL_CALIB_MIN_OFFSET     2       // default 0
#define PREF_PEDAL_CALIB_MAX_OFFSET     4       // default 1023

// each pedal maintains 3 distinct curves consisiting of upto 4 points
// where the MIN is always the 0th point, and the MAX is always the
// CURVE_TYPE + 1'th point. On those two "special points", the x values
// are fixed at 0 and 127, respecitvely, and the y position is used
// in my current pedal handling.

#define PREF_PEDAL_POINTS_OFFSET        6       // word boundry

#define PEDAL_POINTS_OFFSET_X           0
#define PEDAL_POINTS_OFFSET_Y           1
#define PEDAL_POINTS_OFFSET_WEIGHT      2
#define PEDAL_POINT_PREF_SIZE           4       // word boundry

#define PREF_BYTES_PER_CURVE   (MAX_CURVE_POINTS * PEDAL_POINT_PREF_SIZE)
#define CURVE_BYTES_PER_PEDAL  (MAX_PEDAL_CURVES * PREF_BYTES_PER_CURVE)
#define PREF_BYTES_PER_PEDAL   (PREF_PEDAL_POINTS_OFFSET + CURVE_BYTES_PER_PEDAL)
#define PREF_PEDAL(i)          (PREF_PEDAL0 + (i)*PREF_BYTES_PER_PEDAL)

#define PREF_PEDAL_MODE(p)              (PREF_PEDAL(p) + PREF_PEDAL_MODE_OFFSET)
#define PREF_PEDAL_CURVE_TYPE(p)        (PREF_PEDAL(p) + PREF_PEDAL_CURVE_TYPE_OFFSET)
#define PREF_PEDAL_CURVE(p,c)           (PREF_PEDAL(p) + PREF_PEDAL_POINTS_OFFSET + (c)*PREF_BYTES_PER_CURVE)
#define PREF_PEDAL_CURVE_POINT(p,c,i)   (PREF_PEDAL_CURVE(p,c) + (i)*PEDAL_POINT_PREF_SIZE)

#define getPrefPedalMode(p)             (getPref8(PREF_PEDAL_MODE(p)))
#define getPrefPedalCurve(p)            (getPref8(PREF_PEDAL_CURVE_TYPE(p)))
#define getPrefPedalMin(p)              (getPref8(PREF_PEDAL_CURVE_POINT(p,getPrefPedalCurve(p),0) + PEDAL_POINTS_OFFSET_Y))
#define getPrefPedalMax(p)              (getPref8(PREF_PEDAL_CURVE_POINT(p,getPrefPedalCurve(p),getPrefPedalCurve(p)+1) + PEDAL_POINTS_OFFSET_Y))
#define getPrefPedalCalibMin(p)         (getPref16(PREF_PEDAL(p) + PREF_PEDAL_CALIB_MIN_OFFSET))
#define getPrefPedalCalibMax(p)         (getPref16(PREF_PEDAL(p) + PREF_PEDAL_CALIB_MAX_OFFSET))

#define setPrefPedalMode(p,i)           setPref8(PREF_PEDAL_MODE(p),(i))
#define setPrefPedalCurve(p,i)          setPref8(PREF_PEDAL_CURVE_TYPE(p),(i))
#define setPrefPedalCalibMin(p,i)       setPref16(PREF_PEDAL(p) + PREF_PEDAL_CALIB_MIN_OFFSET, (i))
#define setPrefPedalCalibMax(p,i)       setPref16(PREF_PEDAL(p) + PREF_PEDAL_CALIB_MAX_OFFSET, (i))


//-----------------------------
// midi monitor settings
//-----------------------------

#define PREF_MONITOR_OUTPUT    		PREF_PEDAL(NUM_PEDALS + 1)   // off, USB, SERIAL, FOLLOW, default(off)

#define PREF_MONITOR_USB1_IN		(PREF_MONITOR_OUTPUT + 1)	// eight bytes for monitoring input ports
#define PREF_MONITOR_USB2_IN		(PREF_MONITOR_USB1_IN + 1)
#define PREF_MONITOR_USB3_IN		(PREF_MONITOR_USB1_IN + 2)
#define PREF_MONITOR_USB4_IN		(PREF_MONITOR_USB1_IN + 3)
#define PREF_MONITOR_HOST1_IN		(PREF_MONITOR_USB1_IN + 4)
#define PREF_MONITOR_HOST2_IN		(PREF_MONITOR_USB1_IN + 5)
#define PREF_MONITOR_RPI_IN			(PREF_MONITOR_USB1_IN + 6)
#define PREF_MONITOR_HUB_IN			(PREF_MONITOR_USB1_IN + 7)

#define PREF_MONITOR_USB1_OUT		(PREF_MONITOR_HUB_IN + 1)	// eight bytes for monitoring input ports
#define PREF_MONITOR_USB2_OUT		(PREF_MONITOR_USB1_OUT + 1)
#define PREF_MONITOR_USB3_OUT		(PREF_MONITOR_USB1_OUT + 2)
#define PREF_MONITOR_USB4_OUT		(PREF_MONITOR_USB1_OUT + 3)
#define PREF_MONITOR_HOST1_OUT		(PREF_MONITOR_USB1_OUT + 4)
#define PREF_MONITOR_HOST2_OUT		(PREF_MONITOR_USB1_OUT + 5)
#define PREF_MONITOR_RPI_OUT		(PREF_MONITOR_USB1_OUT + 6)
#define PREF_MONITOR_HUB_OUT		(PREF_MONITOR_USB1_OUT + 7)

#define PREF_MONITOR_CHANNEL1       (PREF_MONITOR_HUB_OUT + 1) 		// 16 bytes to monitor specific midi channels


#define PREF_MONITOR_SYSEX              (PREF_MONITOR_CHANNEL1+16)     // off, on, Detail         default(2=Detail)
#define PREF_MONITOR_ACTIVESENSE        (PREF_MONITOR_SYSEX+1)         // off, on                 default(0==off)
#define PREF_MONITOR_NOTE_ON            (PREF_MONITOR_SYSEX+2)
#define PREF_MONITOR_NOTE_OFF           (PREF_MONITOR_SYSEX+3)
#define PREF_MONITOR_VELOCITY           (PREF_MONITOR_SYSEX+4)      // "after touch poly"
#define PREF_MONITOR_PROGRAM_CHG        (PREF_MONITOR_SYSEX+5)
#define PREF_MONITOR_AFTERTOUCH         (PREF_MONITOR_SYSEX+6)
#define PREF_MONITOR_PITCHBEND          (PREF_MONITOR_SYSEX+7)

// ftp specifics
// one or both of the MONITOR_FTP_COMMANDS or VALUES must be ON
// to see specific FTP commadns and replies

#define PREF_MONITOR_FTP                (PREF_MONITOR_SYSEX+8)
#define PREF_MONITOR_PARSE_FTP_PATCHES  (PREF_MONITOR_FTP+0)
#define PREF_MONITOR_FTP_NOTE_INFO      (PREF_MONITOR_FTP+1)
#define PREF_MONITOR_FTP_TUNING_MSGS    (PREF_MONITOR_FTP+2)
#define PREF_MONITOR_FTP_COMMANDS       (PREF_MONITOR_FTP+3)
#define PREF_MONITOR_FTP_VALUES         (PREF_MONITOR_FTP+4)
#define PREF_MONITOR_FTP_POLY_MODE      (PREF_MONITOR_FTP+5)
#define PREF_MONITOR_FTP_BEND_MODE      (PREF_MONITOR_FTP+6)
#define PREF_MONITOR_FTP_VOLUME         (PREF_MONITOR_FTP+7)
#define PREF_MONITOR_FTP_BATTERY        (PREF_MONITOR_FTP+8)
#define PREF_MONITOR_FTP_SENSITIVITY    (PREF_MONITOR_FTP+9)
#define PREF_MONITOR_KNOWN_FTP_COMMANDS     (PREF_MONITOR_FTP+10)
#define PREF_MONITOR_UNKNOWN_FTP_COMMANDS   (PREF_MONITOR_FTP+11)

#define PREF_MONITOR_CCS                (PREF_MONITOR_FTP+12)
    // all other CC's (which should be displayed with standard midi names if known)
#define PREF_MONITOR_EVERYTHING_ELSE    (PREF_MONITOR_CCS+1)
    // general catch all


//-----------------------
// performance filter
//-----------------------

#define PREF_PERF_FILTER                (PREF_MONITOR_EVERYTHING_ELSE + 1)
#define PREF_PERF_FILTER_BENDS          (PREF_PERF_FILTER + 1)		
#define PREF_MONITOR_PERFORMANCE        (PREF_PERF_FILTER + 2)		// unused at this time


//-----------------------
// total
//-----------------------

#define NUM_EEPROM_USED       (PREF_MONITOR_PERFORMANCE + 1)



//--------------------------------------------------------------------------------
// API
//--------------------------------------------------------------------------------

extern uint8_t pref[NUM_EEPROM_USED];
    // for inline speed - NOT for use by clients


inline uint8_t  getPref8(int i)      { return pref[i]; }
inline bool     getPrefBool(int i)   { return (bool) pref[i]; }
inline uint16_t getPref16(int i)     { uint16_t *p=(uint16_t *) &pref[i];  return *p; }

extern void clear_prefs();
extern bool init_global_prefs();
	// returns TRUE if the prefs were automatically reset

extern void save_global_prefs();

extern void setPref8(int i, uint8_t val);
extern void setPrefBool(int i, bool val);
extern void setPref16(int i, uint16_t val);

extern bool prefs_changed();
    // are they changed since last save?
extern bool pref_changed8(int i);
extern bool pref_changed16(int i);

extern void restore_prefs();
    // restore them to last saved state
extern void restore_pref8(int i);
extern void restore_pref16(int i);
extern void setDefaultPrefs();
    // should be called after multiple calls to restore_pref
    // is safe - does not re-read or alter write thru cache


extern uint8_t portMonitorPref(int p, int off);
    // returns the preference setting for a port
    // defering to the default settings if the port
    // has it's main pref set to "default"

extern int16_t getPrefMin(int i);
extern int16_t getPrefMax(int i);
extern const char **getPrefStrings(int i);
