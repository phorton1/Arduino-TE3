//-----------------------------------------------
// defines.h
//-----------------------------------------------

#pragma once

#include <Arduino.h>

#define USB_SERIAL_PORT     Serial
#define HUB_SERIAL_PORT     Serial7
#define RPI_SERIAL_PORT     Serial8


extern void handleSerial();
	// in serial.cpp


//-------------------------------------
// PINS
//-------------------------------------
// Arbitrary initial picks for Teensy 4.1 pins

// Pins "reserved" by choices of Serial Ports
// 		#define PIN_SERIAL1_RX		0
// 		#define PIN_SERIAL1_TX		1
// 		#define PIN_SERIAL2_RX		7
// 		#define PIN_SERIAL2_TX		8
// 		#define PIN_SERIAL3_RX		15 	// A1
// 		#define PIN_SERIAL3_TX		14	// A0
// 		#define PIN_SERIAL4 RX		16	// A2	SCL1
// 		#define PIN_SERIAL4_TX		17	// A3	SDA1
// 		#define PIN_SERIAL5_RX		21	// A7
// 		#define PIN_SERIAL5_TX		20	// A6
// 		#define PIN_SERIAL6_RX		25	// A11	SDA2
// 		#define PIN_SERIAL6_TX		24	// A10	SCL2
// #define PIN_SERIAL7_RX		28	// HUB_SERIAL_PORT
// #define PIN_SERIAL7_TX		29
// #define PIN_SERIAL8_RX		34	// RPI_SERIAL_PORT
// #define PIN_SERIAL8_TX		35

#define PIN_SENSE_RPI_RUN       20     // sense rpi RUN (REBBOOT) pin, HIGH == rpi has voltage
#define PIN_SENSE_RPI_READY     21     // sense rpi GPIO25, HIGH == my program has initialized
#define PIN_RPI_BOOT       		      // HIGH == REBOOT (to base of transistor)

#define PIN_LED_ALIVE  			13		// onboard LED
#define PIN_LED_RPI_RUN			36		// GREEN LED (wimpy with 220 ohm resistor but scared about 4.1 4ma pin limit)
#define PIN_LED_RPI_READY		38		// BLUE LED (bright with 220 ohm reisitor, prob about 7ma)

#define PIN_ROTARY_INTERRUPT   	30
	// arbitrary and untested



