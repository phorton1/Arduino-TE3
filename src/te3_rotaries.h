//----------------------------------------------------------------
// rotaryBoard.h
//----------------------------------------------------------------
// rotary board implementation using interrupt driven
// i2C based mpc23017 3 wire communications

#pragma once

#include "defines.h"

class te3_rotaries
	// mcp23017 based board that handles four rotary
	//      encoders with buttons.
	//
	// The default teensy Wire library frequency is 100 kHz
	//      works at 500kHz with 1K pullups on SDA & SCL
	//          those pullups sre on the T3 mother_board
	//          and not the rotary_board.
	//      doesn't work at 1Mhz
	//
	// The rotary controls values are 0..127
	//
	// The interrupt instantaneously changes the rotary and
	// button values and does NOT call back to the user.
	// It is expected that a secondary process will handle
	// button debouncing.
{
public:

	te3_rotaries() {}

	static void init();
	static void loop();

	static void setValue(uint8_t num, uint8_t val, bool prevent_event = false)
	{
		rot_value[num] = val;
		if (prevent_event)
			last_value[num] = val;
	}

	static uint8_t getValue(uint8_t num)
		{ return rot_value[num]; }

	static bool getRawButton(uint8_t num)	// NOT debounced
		{ return button_value[num]; }

private:

	static int s_int_pin;
	static uint32_t s_freq;
	static volatile int s_int_count;
	static volatile uint16_t s_gpio_val;

	static float rot_value[NUM_ROTARIES];			// instantenous set by interrupt
	static bool button_value[NUM_ROTARIES];
	static uint8_t last_value[NUM_ROTARIES];			// last value to generate event in loop()

	static void mpcWrite(uint8_t reg, uint8_t data);
	static void mpcWrite2(uint8_t reg, uint8_t data);
	static uint8_t mpcReadByte(uint8_t reg);
	static void mpcRead(uint8_t reg, uint8_t *buf, int bytes);

	static void swIRQ();
	static void calcRotary(int i, uint16_t last_val);

	static void dumpMpcRegs(const char *);  // debugging

};


