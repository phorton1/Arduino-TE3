//-----------------------------------------------
// defines.h
//-----------------------------------------------

#pragma once

#include <Arduino.h>

#define TEENSY_EXPRESSION_VERSION  "3.0"



#define NUM_BUTTON_ROWS		5
#define NUM_BUTTON_COLS		5
#define NUM_BUTTONS			(NUM_BUTTON_ROWS * NUM_BUTTON_COLS)

#define USB_SERIAL_PORT     Serial
#define RPI_SERIAL_PORT     Serial1		// pins 0,1
#define DBG_SERIAL_PORT		Serial7		// pins 28,29
#define HUB_SERIAL_PORT     Serial8		// pins 34,35

// Serial port accessors (for speed)

extern Stream *TE3_DEBUG_STREAM;
extern Stream *HUB_DEBUG_OUTPUT;
extern Stream *RPI_DEBUG_OUTPUT;
extern Stream *MONITOR_OUTPUT;


extern void initDebugStreams();
	// in TE3.ino


extern void handleSerial();
	// in serial.cpp

//-------------------------------------
// PINS
//-------------------------------------
// indented Serial pins in use
//
// 	#define PIN_SERIAL1_RX		0		// RPI_SERIAL_PORT
// 	#define PIN_SERIAL1_TX		1
// 		#define PIN_SERIAL2_RX		7
// 		#define PIN_SERIAL2_TX		8
// 		#define PIN_SERIAL3_RX		15
// 		#define PIN_SERIAL3_TX		14
// 		#define PIN_SERIAL4 RX		16
// 		#define PIN_SERIAL4_TX		17
// 		#define PIN_SERIAL5_RX		21
// 		#define PIN_SERIAL5_TX		20
// 		#define PIN_SERIAL6_RX		25
// 		#define PIN_SERIAL6_TX		24
// #define PIN_SERIAL7_RX		28		// DBG_SERIAL_PORT
// #define PIN_SERIAL7_TX		29
// #define PIN_SERIAL8_RX		34		// HUB_SERIAL_PORT
// #define PIN_SERIAL8_TX		35

// rPi interface

#define PIN_SENSE_RPI_RUN       16		// sense rpi RUN (REBBOOT) pin, HIGH == rpi has voltage
#define PIN_SENSE_RPI_READY     30		// sense rpi GPIO12, HIGH == my program has initialized
#define PIN_RPI_BOOT       		31		// HIGH == REBOOT (to base of transistor)

// LEDs

#define PIN_LED_T3_BUSY 	4		// RED LED with 220 ohm resistor
#define PIN_LED_RPI_RUN		5		// GREEN LED with 100 ohm resistor
#define PIN_LED_RPI_READY	6		// BLUE LED with 220 ohm reisitor

// display (ili9488_t3)


#define PIN_TFT_DC			9
#define PIN_TFT_CS			10  // hardware SPI0 teensy 4.1
#define PIN_TFT_MOSI		11  // hardware SPI0 teensy 4.1
#define PIN_TFT_MISO		12  // hardware SPI0 teensy 4.1
#define PIN_TFT_SCLK		13	// hardware SPI0 teensy 4.1
#define PIN_TS_CS			3


// rotary board

#define PIN_ROTARY_INTERRUPT   	17
// #define PIN_SDA				18
// #define PIN_SCL				19

// row boards

#define PIN_LED_DIN				20	// only pin on teensy4.x that supports ws3812bSerial
#define PIN_BTN_CLK				21
#define PIN_BTN_DIN				22
#define PIN_BTN_SENSE			23

// pedals
// the pin numbers in the schematic are currently backwards
// as the LEFTMOST (from the front) is #1, but the PCB is
// designed from the back, lol

#define PIN_PEDAL_0				27	// A13
#define PIN_PEDAL_1				26	// A12
#define PIN_PEDAL_2				25	// A11
#define PIN_PEDAL_3				24	// A10



// in TE3.ino

void setTE3Busy();
void clearTE3Busy();


//-----------------------------------------------------------
// STUFF RUDELY IMPORTED FROM TE1
//-----------------------------------------------------------
// TE1 specific defines

#define NUM_PORTS           8       // ports defined in midiQueue.h
#define NUM_PEDALS          4
#define NUM_MIDI_PORTS      8

#define THE_SYSTEM_BUTTON   4

#define BUTTON_NUM(r,c)    ((r) * NUM_BUTTON_COLS + (c))
#define BUTTON_ROW(i)      ((i) / NUM_BUTTON_COLS)
#define BUTTON_COL(i)      ((i) % NUM_BUTTON_COLS)

#define BUTTON_MOVE_UP          12
#define BUTTON_MOVE_LEFT        16
#define BUTTON_MOVE_RIGHT       18
#define BUTTON_MOVE_DOWN        22
#define BUTTON_SELECT           17

#define PEDAL_SYNTH     0
#define PEDAL_LOOP      1
#define PEDAL_WAH       2
#define PEDAL_GUITAR    3

#define LOOPER_NUM_TRACKS_TIMES_LAYERS    (LOOPER_NUM_TRACKS * LOOPER_NUM_LAYERS)


typedef struct
    // structure common to New and Old rig patches
{
    int prog_num;
    const char *short_name;         // SHOULD BE 6 CHARS OR LESS
    const char *long_name;          // NOT USED IN NEW RIG
    bool mono_mode;                 // NOT USED IN OLD RIG
}   synthPatch_t;


// .........

// ansi colors

#define ansi_color_black 	            30
#define ansi_color_red 	     	        31
#define ansi_color_green 	            32
#define ansi_color_brown 	 	        33
#define ansi_color_blue 	            34
#define ansi_color_magenta 	 	        35
#define ansi_color_cyan 	            36
#define ansi_color_light_grey 	        37

#define ansi_color_grey  	            90
#define ansi_color_light_red 	        91
#define ansi_color_light_green 	        92
#define ansi_color_yellow 		        93
#define ansi_color_light_blue  	        94
#define ansi_color_light_magenta        95
#define ansi_color_light_cyan 	        96
#define ansi_color_white  		        97

#define ansi_color_bg_black 	        40
#define ansi_color_bg_red 	     	    41
#define ansi_color_bg_green 	        42
#define ansi_color_bg_brown 	 	    43
#define ansi_color_bg_blue 	            44
#define ansi_color_bg_magenta 	 	    45
#define ansi_color_bg_cyan 	            46
#define ansi_color_bg_light_grey 	    47

#define ansi_color_bg_grey  	        100
#define ansi_color_bg_light_red 	    101
#define ansi_color_bg_light_green 	    102
#define ansi_color_bg_yellow 		    103
#define ansi_color_bg_light_blue  	    104
#define ansi_color_bg_light_magenta     105
#define ansi_color_bg_light_cyan 	    106
#define ansi_color_bg_white  		    107


// int_rect

class int_rect
{
public:

    int_rect()
    {
        xs = 0;
        ys = 0;
        xe = 0;
        ye = 0;
    }

    int_rect(int16_t ixs, int16_t iys, int16_t ixe, int16_t iye)
    {
        xs = ixs;
        ys = iys;
        xe = ixe;
        ye = iye;
    }

    void assign(int16_t ixs, int16_t iys, int16_t ixe, int16_t iye)
    {
        xs = ixs;
        ys = iys;
        xe = ixe;
        ye = iye;
    }


    int16_t width() { return xe-xs+1; }
    int16_t height()  { return ye-ys+1; }

    int16_t xs;
    int16_t ys;
    int16_t xe;
    int16_t ye;
};


//----------------------------------------------------------------
// interface to _usbNames.c
//----------------------------------------------------------------
// Used in TE3.ino to setup self USB device, and in fileCommand.cpp
// to reply with WASSUP and the Teensy serial number.
//
// I am still using my copied _usb.c and _usbdesc.c, although
// I *could* get away with just using the official _usbNames.c
// approach.  My _usb.c was introduced to allow me to change the
// device descriptors via preferences, mostly to spoof the FTP,
// by deferring Paul's static usb_init() call to a runtime call.
//
// The only thing it actually does in this incarnation is to
// copy the actual teensy serial number into my serial number
// descriptor before initializing the USB devie, so that each
// device has a unique TE3xxxx serial number.

extern "C" {
    extern void my_usb_init();          	// in usb.c
    // extern void setFTPDescriptors();    	// commented out in _usbNames.c
	extern const char *getUSBSerialNum();	// in _usbNames.c
}


//----------------------------------------
// compatibility layer for fileSystem (TE1/TE2/TE3)
//----------------------------------------

#define ACTIVE_FILE_SYS_DEVICE	TE3_DEBUG_STREAM
	// used in fileSerial.cpp
#define SERIAL_DEVICE			(*TE3_DEBUG_STREAM)
	// overloaded name unfortunately ...
	// NOT used but needed to compile fileSerial.cpp handleSerialData() method


// end of TE3 defines.h
