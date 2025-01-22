//-----------------------------------------------
// defines.h
//-----------------------------------------------
// Although I have prototyped this for an ESP32.
// it is not clear there are benefits to using an ESP32.
// Telnet *might* be handy for fileServer across the room.
//
// I'm afraid there are not enough serial ports on ESP32's,
// and that a Teensy4.0 would be better, esp as we still
// have not accounted for the "Teensy Expression" portion,
// and might actually want a TE4.1 here.


#pragma once

#ifdef ESP32
	#define WITH_WIFI			0
	#define WITH_TELNET     	0
	#define WITH_ROTARIES		0		// must be zero
#else	// teensy 4.1
	#define WITH_WIFI			0
	#define WITH_TELNET     	0
	#define WITH_ROTARIES		0
#endif


#include <Arduino.h>

#define USB_SERIAL_PORT     Serial

#ifdef ESP32
	#include <HardwareSerial.h>
	#include <Preferences.h>
	extern HardwareSerial HUB_SERIAL_PORT;
	extern Preferences preferences;
		// in TE3.ino
#else
	#define HUB_SERIAL_PORT     Serial1
	#define RPI_SERIAL_PORT     Serial2
#endif


#ifdef ESP32
	#if WITH_WIFI
		#include "WiFi.h"
		extern void connectWifi(const String &ssid, const String &pass);
			// in te3_wifi.cpp

		#if WITH_TELNET
			#include <ESPTelnetStream.h>
			extern void init_telnet();
			extern ESPTelnetStream telnet;
			extern bool telnet_started;
				// in te3_serial.cpp
		#endif
	#endif
#endif


extern void handleSerial();
	// in serial.cpp


//-------------------------------------
// PINS
//-------------------------------------

#ifdef ESP32
	#define PIN_SENSE_RPI_RUN       35      // sense rpi RUN (REBBOOT) pin, HIGH == rpi has voltage
	#define PIN_SENSE_RPI_READY     33      // sense rpi GPIO25, HIGH == my program has initialized
	#define PIN_RPI_BOOT       		32      // HIGH == REBOOT (to base of transistor)

	#define PIN_LED_ALIVE  			2		// RED LED
	#define PIN_LED_RPI_RUN			21		// GREEN LED
	#define PIN_LED_RPI_READY		22		// BLUE LED

	#define PIN_HUB_SERIAL_RX   	27		// HARDWARE SERIAL1 <-> TE_HUB
	#define PIN_HUB_SERIAL_TX   	26		// The default pins did not work

	#define PIN_SERIAL2_RX   		16     	// These ARE the default ESP32 Serial2 pins
	#define PIN_SERIAL2_TX   		17     	// They are untested at this time.
#else

	#define PIN_ROTARY_INTERRUPT   	22
		// conflicts with PIN_LED_RPI_READY_PIN
		// rotaries were only tried on an Arduino
#endif

