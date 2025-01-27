//-------------------------------------------
// TE3.ino
//-------------------------------------------
// TE3 is the third version of the teensyExpression pedal.
//
// It integrates the Looper and TE into a single box, minimizing
// external cables, connectors, and power supplies.
//
// This code runs on a teensy 4.1 and inherits the functionality
// from the teensyPiLooper program to communicate with the
// circle rPi Looper program, now running on an rPi 2W, via Serial,
// as well as adding functionality to communicate with the new TE3_Hub
// USB Audio Device running on a teensy 4.0 with a revD SGTL5000 sound
// card, which replaces the iRigHD2 from the previous Looper2 box.


#include "src/defines.h"
#include <myDebug.h>
#include "src/te3_leds.h"

#define WITH_ROTARIES		0
// #define WITH_MIDI_HOST      1
	// defined in midiHost.cpp

#if WITH_ROTARIES
    #include "src/rotaryBoard.h"
#endif

#if WITH_ROTARIES
    #include "src/midiHost.h"
#endif


extern "C" {
    extern void my_usb_init();          	// in usb.c
    // extern void setFTPDescriptors();    	// _usbNames.c
	extern const char *getUSBSerialNum();	// _usbNames.c
}



//---------------------------------------------
// 595 test
//---------------------------------------------

void test595()
{
}



//---------------------------------------------
// setup
//---------------------------------------------

void setup()
{
    // setColorString(COLOR_CONST_DEFAULT, "\033[94m");  // example for bright blue
        // TE3's normal (default) display color is green
        // TE3_hubs normal display color is bright blue
        // Looper's normal display color, is cyan

	//-------------------------------------------
	// initialize usb and serial ports
	//-------------------------------------------

    delay(500);
	my_usb_init();
	USB_SERIAL_PORT.begin(115200);

	delay(500);
    display(0,"TE3.ino setup() started",0);
	HUB_SERIAL_PORT.begin(115200);

    #if PIN_LED_T3_ALIVE
		pinMode(PIN_LED_T3_ALIVE,OUTPUT);
        digitalWrite(PIN_LED_T3_ALIVE,0);
    #endif


	pinMode(PIN_LED_RPI_RUN,OUTPUT);
	pinMode(PIN_LED_RPI_READY,OUTPUT);
	#if 1
		for (int i=0; i<7; i++)
		{
			digitalWrite(PIN_LED_RPI_RUN,i&1);
			digitalWrite(PIN_LED_RPI_READY,!(i&1));
			delay(200);
		}
	#endif
	digitalWrite(PIN_LED_RPI_RUN,0);
	digitalWrite(PIN_LED_RPI_READY,0);


    initLEDs();
    LEDFancyStart();

	
    #if WITH_ROTARIES
        rotaryBoard::begin(PIN_ROTARY_INTERRUPT);
    #endif

	#if 0
		pinMode(PIN_BTN_CLK,OUTPUT);
		pinMode(PIN_BTN_DIN,OUTPUT);
		digitalWrite(PIN_BTN_CLK,0);
		digitalWrite(PIN_BTN_DIN,0);
		pinMode(PIN_BTN_SENSE,INPUT_PULLDOWN);
	#endif

    display(0,"TE3.ino setup() finished",0);
}




//--------------------------------------
// rotary board
//--------------------------------------

#if WITH_ROTARIES

    static uint8_t last_rot[NUM_ROTARIES];

    void handleRotaries()
    {
        bool changed = false;
        for (int i=0; i<NUM_ROTARIES; i++)
        {
            uint8_t val = rotaryBoard::getValue(i);
            if (last_rot[i] != val)
            {
                changed = 1;
                last_rot[i] = val;
            }
        }

        if (changed)
            display(0,"rotaries:  %-3d  %-3d  %-3d  %-3d",
                last_rot[0],
                last_rot[1],
                last_rot[2],
                last_rot[3]);
    }

#endif



//---------------------------------------------
// loop()
//---------------------------------------------

void loop()
{
    #if PIN_LED_T3_ALIVE
        static bool flash_on = 0;
        static uint32_t flash_last = 0;
        uint32_t flash_now = millis();
        if (flash_now > flash_last + 250)
        {
            flash_last = flash_now;
            flash_on = !flash_on;
            digitalWrite(PIN_LED_T3_ALIVE,flash_on);
        }
    #endif

    #if WITH_ROTARIES
        handleRotaries();
    #endif

    handleSerial();
    delay(1);



	//----------------------------------
	// 74hc595 button test
	//----------------------------------
	// I think maybe better would be to supply voltage to all the
	// pins and multiplex the inputs, but I would need to order 495's
	// and redesign the row_board.
	//
	// When I first implemented this as a loopt to read all buttons,
	// there was an issue with timing, both with the latching
	// out outputs, AND the reading of the input.  I presume
	// it's because of the capacitance of the wires and traces,
	// and would probably get worse when I add more buttons
	// to each row_board and add more row_boards.
	//
	// This algorithm polls starts the 595 bit process on the 0th
	// itereation, then reads subsequent buttons each ms thereafter.
	// It only uses a few us per loop, and defers event handling to some
	//
	// Note that need to do a full 8 cycles per row board, and assumes we
	// are using the 595 B-F outputs for the attached buttons.
	// The test prototype board only has two buttons, with the left
	// button is on the 595 'B' channel, and the right button is on the
	// 'F' channel.  Therefor their "actual" button numbers are 0 and 5.


	#define dbg_buttons 	0

	#define PROTO_LEFT_BNUM		0		// 'B' on first row_board
	#define PROTO_RIGHT_BNUM	4		// 'F' on first row_board

	//-------------------------------------------
	// RAW BUTTON IO
	//-------------------------------------------

	static int button_num = -1;
	static bool cur_button_state[NUM_BUTTONS];		// contantly updated

	#define LATCH_DELAY		2			// us
	#define BTN_READ_TIME	0			// every ms

	static uint32_t btn_read_time = 0;
	uint32_t now = millis();
	if (now - btn_read_time > BTN_READ_TIME)
	{
		btn_read_time = now;

		// the clock is always left LOW be
		if (button_num == -1)	// starting new cycle
		{
			digitalWrite(PIN_BTN_DIN,1);
			digitalWrite(PIN_BTN_CLK,1);		// 1 goes into the shift register
			delayMicroseconds(LATCH_DELAY);
			digitalWrite(PIN_BTN_CLK,0);
			digitalWrite(PIN_BTN_DIN,0);

			delayMicroseconds(LATCH_DELAY);
			digitalWrite(PIN_BTN_CLK,1);		// 0 goes into shift register 1 goes to output A
			delayMicroseconds(LATCH_DELAY);
			digitalWrite(PIN_BTN_CLK,0);

			delayMicroseconds(LATCH_DELAY);
			digitalWrite(PIN_BTN_CLK,1);		// 0 goes into shift register 1 goes to output B
			delayMicroseconds(LATCH_DELAY);
			digitalWrite(PIN_BTN_CLK,0);

			button_num++;						// there will be almost 1 full ms before we read button zero
		}
		else
		{
			cur_button_state[button_num] = digitalRead(PIN_BTN_SENSE);
			// display(dbg_buttons+1,"button_num[%d] = %d",button_num,cur_button_state[button_num]);

			digitalWrite(PIN_BTN_CLK,1);		// 1 goes to next pin
			delayMicroseconds(LATCH_DELAY);
			digitalWrite(PIN_BTN_CLK,0);
			button_num++;

			if (button_num == NUM_BUTTONS)		// done with cycle
			{
				button_num = -1;
				if (dbg_buttons < 0)
					delay(1000);
			}
			else if (button_num % NUM_BUTTON_COLS == 0)		// skip outputs G,H, and subsequent A
			{
				for (int i=0; i<3; i++)
				{
					delayMicroseconds(LATCH_DELAY);
					digitalWrite(PIN_BTN_CLK,1);
					delayMicroseconds(LATCH_DELAY);
					digitalWrite(PIN_BTN_CLK,0);
				}
			}
		}
	}	// btn_read_time


	//-------------------------------------------
	// PROCESS BUTTON CHANGES
	//-------------------------------------------
	// this will be done by a non-time critical process

	static bool prev_button_state[NUM_BUTTONS];		// handled by event handler of some kind

	for (int num=0; num<NUM_BUTTONS; num++)
	{
		bool state = cur_button_state[num];
		if (prev_button_state[num] != state)
		{
			prev_button_state[num] = state;
			display(dbg_buttons,"BUTTON_NUM[%d] changed to %d",num,state);

			int use_button =
				num == PROTO_LEFT_BNUM ? 0 :
				num == PROTO_RIGHT_BNUM ? 1 : -1;

			if (use_button >= 0)
			{
				setLED(use_button,state?LED_BLUE:LED_BLACK);
				showLEDs();
			}
		}
	}	// process the buttons



}	// loop()


// end of TE3.ino
