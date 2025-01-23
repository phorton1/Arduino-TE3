//----------------------------------------------------------------
// rotaryBoard.h
//----------------------------------------------------------------
// rotary board implementation using interrupt driven
// i2C based mpc23017 3 wire communications


#include "defines.h"

#define NUM_ROTARIES        4

class rotaryBoard
	// mcp23017 based board that handles four rotary
	//      encoders with buttons.
	//
	// The default teensy Wire library frequency is 100 kHz
	//      works at 500kHz with 1K pullups on SDA & SCL
	//          those pullups will likely go on the T3 board
	//          and not the rotary board.
	//      may want decoupling caps on the rotary board
	//          but there are none in my test circuit
	//      doesn't work at 1Mhz
	//
	// The rotary controls values are 0..127
{
public:

	rotaryBoard() {}

	static void begin(int int_pin, uint32_t freq=100000);
	static void process();

	static void setValue(uint8_t num, uint8_t val)
		{ rot_value[num] = val; }

	static uint8_t getValue(uint8_t num)
		{ return rot_value[num]; }

private:

	static int s_int_pin;
	static uint32_t s_freq;
	static volatile int s_int_count;
	static volatile uint16_t s_gpio_val;

	static float rot_value[NUM_ROTARIES];

	static void mpcWrite(uint8_t reg, uint8_t data);
	static void mpcWrite2(uint8_t reg, uint8_t data);
	static uint8_t mpcReadByte(uint8_t reg);
	static void mpcRead(uint8_t reg, uint8_t *buf, int bytes);

	static void swIRQ();
	static void calcRotary(int i, uint16_t last_val);

	static void dumpMpcRegs(const char *);  // debugging

};


