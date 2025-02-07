//-----------------------------------------------
// defines.h
//-----------------------------------------------

#pragma once

#include <Arduino.h>

#define NUM_BUTTON_ROWS		5
#define NUM_BUTTON_COLS		5
#define NUM_BUTTONS			(NUM_BUTTON_ROWS * NUM_BUTTON_COLS)

#define USB_SERIAL_PORT     Serial
#define RPI_SERIAL_PORT     Serial1		// 0,1
#define DBG_SERIAL_PORT		Serial7		// 28,29
#define HUB_SERIAL_PORT     Serial8		// 34,35

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

#define PIN_LED_T3_ALIVE 	13		// onboard LED hearbeat
#define PIN_LED_T3_BUSY 	4		// RED LED with 220 ohm resistor
#define PIN_LED_RPI_RUN		5		// GREEN LED with 100 ohm resistor
#define PIN_LED_RPI_READY	6		// BLUE LED with 220 ohm reisitor

// display (ili9488_t3)

#define PIN_LCD_SCLK		7
#define PIN_TS_CS			8
#define PIN_LCD_DC			9
#define PIN_LCD_CS			10
// #define PIN_MOSI			11
// #define PIN_MISO			12


// rotary board

#define PIN_ROTARY_INTERRUPT   	17
// #define PIN_SDA				18
// #define PIN_SCL				19

// row boards

#define PIN_LED_DIN				20	// only pin on teensy4.x that supports ws3812bSerial
#define PIN_BTN_CLK				21
#define PIN_BTN_DIN				22
#define PIN_BTN_SENSE			23	


// in TE3.ino

void setTE3Busy();
void clearTE3Busy();


// end of TE3 defines.h
