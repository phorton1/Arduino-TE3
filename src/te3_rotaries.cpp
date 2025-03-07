//-------------------------------------------------
// te3_rotaries.cpp
//-------------------------------------------------
// rotary board implementation using interrupt driven
// i2C based mpc23017 3 wire communications
//
// detaching and re-attaching the interrupt seems superflous,
//      and inefficient, and did not work well:
//      detachInterrupt(digitalPinToInterrupt(PIN_SWINT));
//
// it may be necessary/useful to put 0.1uf ceramic caps between
//      the rotary pins and ground for hardware debouncing
//      and/or implement more sophisticated hard debouncing.
//
// push_button debouncing done in process()

#include "defines.h"
#include "te3_rotaries.h"
#include <Wire.h>
#include <myDebug.h>
#include "expSystem.h"

#define dbg_rots    0
#define dbg_mpc     -1

// The rotaries I have are 40 incs per rev.
// The sensitivity is an aribrary floating point increment per indent.
// Set here for 360 degrees == 0..127
// Perhaps will be user defined

#define MAX_ROTARY_VALUE    127.0
#define INC_PER_INDENT      (MAX_ROTARY_VALUE/40.0)


// teensy 4.x pin reminders
// #define PIN_SDA     18
// #define PIN_SCL     19

#define MPC_ADDR    0x20

// mpc23017 register addresses (in IOCON mode "bank" zero)
// By virtue of the fact that in this bank mapping, all 8 bit Ax registers
// are followed by their Bx registers, we can use mpcWrite2 to configure
// both the GPAx and GPBx registers, treating them as 16 bit values.

#define IODIRA   0x00   // IO direction  (0 = output, 1 = input (Default))
#define IODIRB   0x01
#define IOPOLA   0x02   // IO polarity   (0 = normal, 1 = inverse)
#define IOPOLB   0x03
#define GPINTENA 0x04   // Interrupt on change (0 = disable, 1 = enable)
#define GPINTENB 0x05
#define DEFVALA  0x06   // Default comparison for interrupt on change (interrupts on opposite)
#define DEFVALB  0x07
#define INTCONA  0x08   // Interrupt control (0 = interrupt on change from previous, 1 = interrupt on change from DEFVAL)
#define INTCONB  0x09
#define IOCON    0x0A   // IO Configuration: bank/mirror/seqop/disslw/haen/odr/intpol/notimp
//#define IOCON 0x0B    // there is only one IOCON register but it is available at two addresses
#define GPPUA    0x0C   // Pull-up resistor (0 = disabled, 1 = enabled)
#define GPPUB    0x0D
#define INTFA    0x0E    // Interrupt flag (read only) : (0 = no interrupt, 1 = pin caused interrupt)
#define INTFB    0x0F
#define INTCAPA  0x10   // Interrupt capture (read only) : value of GPIO at time of last interrupt
#define INTCAPB  0x11
#define GPIOA    0x12   // Port value. Write to change, read to obtain value
#define GPIOB    0x13
#define OLLATA   0x14   // Output latch. Write to latch output.
#define OLLATB   0x15


// names of 16 bit register equivilants for debugging

#define NUM_DUMP_WORDS  10
static const char *reg_name[] = {
    "IODIR",
    "IOPOL",
    "GPINTEN",
    "DEFVAL",
    "INTCON",
    "IOCON",
    "GPPU",
    "INTF",
    "INTCAP",
    "GPIO", };


// member variable declarations

int te3_rotaries::s_int_pin;
uint32_t te3_rotaries::s_freq;
volatile int te3_rotaries::s_int_count;
volatile uint16_t te3_rotaries::s_gpio_val;

float te3_rotaries::rot_value[NUM_ROTARIES];
bool te3_rotaries::button_value[NUM_ROTARIES];
uint8_t te3_rotaries::last_value[NUM_ROTARIES];


//-------------------------------
// te3_rotaries.cpp methods
//-------------------------------

void te3_rotaries::init()   // int int_pin, uint32_t freq /*= 100000*/)
{
    s_freq = 100000;         
    s_int_pin = PIN_ROTARY_INTERRUPT;

    Wire.begin();

    if (dbg_mpc < 0)
        dumpMpcRegs("initializing mpc23017");
    else
        display(dbg_mpc,"te3_rotaries::init() started",0);

    // We use most of the mpc23017 default values, esp the
    // IOCONN (configuration) register which determines the
    // register addrssing scheme as given by the defines above.

    // mpcWrite(IOCONN0,0x00);     // (default)
        // 7 = BANK = use sequential register address scheme (as #defines above)
        // 6 = MIRROR = connect int pins .. they are connected on the TE3 rotary_board
        // 5 = SEQOP = 0 means address pointer increments (as we use it)
        // 4 = DSSLW = slew rate enabled for SDA output (whatever that means)
        // 3 = HAEN = enable hardware address pins for SPI chip variant (we are using the I2C variant)
        // 2 = ODR = configure INT pin as an open drain output (1 overrides INTPOL bit)
        // 1 = INTPOL = 0 = active low interrupts
        // 0 = unused (reads as a zero)

    // We use 3 pins per rotary controller, 2 for the A/B inputs, and one for the button.
    // To optimize the PCB layout, Rotary 3 and 4 are positionally switched

    //    Rotary 0 : A=GPA0, B=GPA1, SW=GPA2, GPA3 unused (tied to ground)
    //    Rotary 1 : A=GPA4, B=GPA5, SW=GPA6, GPA7 unused (tied to ground)
    //    Rotary 2 : A=GPB4, B=GPB5, SW=GPB6, GPB7 unused (tied to ground)
    //    Rotary 3 : A=GPB0, B=GPB1, SW=GPB2, GPB3 unused (tied to ground)

    // mpcWrite2(IODIRA, 0xff);     // (default) 1=set pin to input
    // mpcWrite2(IOPOLA, 0x00);     // (default) 0=set pin to non-inverted polarity
    mpcWrite2(GPINTENA, 0xff);      // 1=set pin to generate interrupt
    // mpcWrite2(DEFVALA,0x00);     // (default) 0=unused default values of zero
    // mpcWrite2(INTCONA,0x00);     // (default) 0=use state change, not defval
    mpcWrite2(GPPUA,  0xff);        // enable pullups

    if (dbg_mpc < 0)
        dumpMpcRegs("after initialization");

    // attach the interrupt

    attachInterrupt(digitalPinToInterrupt(s_int_pin), swIRQ, FALLING);

    if (dbg_mpc == 0)
        display(dbg_mpc,"te3_rotaries::init() finished",0);
}


void te3_rotaries::dumpMpcRegs(const char *what)
{
    uint16_t regs[NUM_DUMP_WORDS];
    memset(regs,0,2*NUM_DUMP_WORDS);
    mpcRead(IODIRA,(uint8_t *)regs, 2*NUM_DUMP_WORDS);
    display(0,"dumpRegs(%s)",what);
    for (int i=0; i<NUM_DUMP_WORDS; i++)
    {
        display(0,"  %-8s = 0x%04x",reg_name[i],regs[i]);
    }
}


void te3_rotaries::mpcWrite(uint8_t reg, uint8_t data)
    // Write a byte to a single register
{
    Wire.setClock(s_freq);
    Wire.beginTransmission(MPC_ADDR);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission ();
}


void te3_rotaries::mpcWrite2(uint8_t reg, uint8_t data)
    // Write the same data byte to two sequential registers
{
    Wire.setClock(s_freq);
    Wire.beginTransmission(MPC_ADDR);
    Wire.write(reg);
    Wire.write(data);
    Wire.write(data);
    Wire.endTransmission ();
}


void te3_rotaries::mpcRead(uint8_t reg, uint8_t *buf, int bytes)
   // Read bytes from sequential registers
{
    Wire.setClock(s_freq);
    Wire.beginTransmission(MPC_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(MPC_ADDR,bytes);
    for (int i=0; i<bytes; i++)
    {
        buf[i] = Wire.read();
    }
}


uint8_t te3_rotaries::mpcReadByte(uint8_t reg)
    // unused - Read a byte from a single register
{
    Wire.setClock(s_freq);
    Wire.beginTransmission(MPC_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(MPC_ADDR,1);
    uint8_t retval = Wire.read();
    return retval;
}


void te3_rotaries::swIRQ()
    // Interrupt Service Routine for the MCP23017.
    // The time to read registers is approximately
    // 12 clock cycles + 8 * the number of bytes.
    //
    // I don't think we care about which pin caused the interrupt.
    // Nor do we care about the potential difference between
    // the values "captured" at the time of the interrupt and
    // the "current" values in the gpio register.
    //
    // Therefore, we want to read 2 bytes, and that should
    // take approximately 28 clock cycles. At 100kHz, thats
    // about 280us. At 200kHz, it would be even less.
{
    s_int_count++;
    uint16_t last_val = s_gpio_val;
    mpcRead(GPIOA, (uint8_t *)&s_gpio_val, 2);
    s_gpio_val = ~s_gpio_val;       // change sense

    for (int i=0; i<NUM_ROTARIES; i++)
        calcRotary(i,last_val);
}


void te3_rotaries::calcRotary(int rot_num, uint16_t last_val)
{
    // logically switch rotary 3 and 4 (zero based 2 and 3)
    // as Rotary3 uses the upper nibble of the 2nd byte

    int mask_num = rot_num;
    if (rot_num == 2) mask_num=3;
    else if (rot_num == 3) mask_num=2;

    // get the button raw value with no debouncing

    uint16_t button_mask = 4 << (mask_num * 4);
    button_value[rot_num] = s_gpio_val & button_mask;

    // check the rotary A pin
    
    uint16_t a_mask = 1 << (mask_num * 4);
    bool cur_a = s_gpio_val & a_mask ? 1 : 0;
    bool last_a = last_val & a_mask ? 1 : 0;

    // return if A has not changed

    if (cur_a == last_a)
        return;

    uint16_t b_mask = 2 << (mask_num * 4);
    bool cur_b = s_gpio_val & b_mask ? 1 : 0;
    float val = rot_value[rot_num];

    if (cur_a == cur_b)
    {
        if (val + INC_PER_INDENT > MAX_ROTARY_VALUE)
            val = MAX_ROTARY_VALUE;
        else
            val += INC_PER_INDENT;
    }
    else
    {
        if (val - INC_PER_INDENT < 0)
            val = 0;
        else
            val -= INC_PER_INDENT;
    }

    rot_value[rot_num] = val;
}



void te3_rotaries::loop()
{
    for (int i=0; i<NUM_ROTARIES; i++)
    {
        uint8_t val = rot_value[i];
        if (last_value[i] != val)
        {
            last_value[i] = val;
            display(dbg_rots,"ROTARY[%d]=%d",i,val);
            theSystem.rotaryEvent(i,val);
        }
    }
}


