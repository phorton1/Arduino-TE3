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

	#if 1
		pinMode(PIN_BTN_CLK,OUTPUT);
		pinMode(PIN_BTN_DIN,OUTPUT);
		digitalWrite(PIN_BTN_CLK,0);
			// initial master clock is LOW for 1st prototype board
			// but will be HIGH for actual inverting board
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





static bool cur_button_state[NUM_BUTTONS];		// contantly updated


void send595bit()
{
	// DIP16 vs SMT chips on breadboard issue
	//
	//  OH' (portH prime) that is forwarded to the next chip
	//	ACTUALLY goes high at the same time as portG, not portH
	//	as one might expect.
	//
	//	On the DIP16 chips it works as I originally designed it.
	//	Howevewr, with the SMT chips there was an anomoly that
	//	was only revealed with the breadboard full of LEDs.
	//
	//	The issue was ultimately resolved by merely writing
	//	a zero to the BTN_CLOCK at the start of each cycle

	#define DEBUG_SLOW	0

	// One full microsecond should be more than enough time
	// for everybody to synchronize and the sense voltage
	// to rise. We use GT (not GTE) to ensure that a full
	// microsecond has passed.

	#if DEBUG_SLOW
		uint32_t BUTTON_LATCH_INTERVAL = 1000000;
	#else
		#define BUTTON_LATCH_INTERVAL	1		// us
	#endif

	#define BUTTON_CYCLE_INTERVAL		33		// ms; 0 for visualizing !DEBUG_SLOW
		// Polling the buttons every 33 ms handles debouncing.
		// Set this to zero on the breadboard with !DEBUG_SLOW
		//		to get enough duty cycle to light up all the leds
		
	static int button_cycle = 0;
		// The 0th cycle cycles the 1 into the shift register.
		// The 1st cycle puts it out to port0A.
		// If we had eight buttons, we would read the 0th (portA)
		// 		on the 2nd cycle.  But we skip portA as our zero'th
		//      button is on portB, so we read button0 (portB) on
		//		the third cycle.
		// Otherwise it's all div and mod by 8.

	static bool in_button_cycle = 0;
		// cycle started every BUTTON_CYCLE_INTERVAL ms
	static uint32_t last_button_cycle = 0;		// ms timer
	static uint32_t last_clock_toggle = 0;		// us timer

	#if DEBUG_SLOW
		if (Serial.available());
		{
			int c = Serial.read();
			if (c == ' ')
				BUTTON_LATCH_INTERVAL = 1;
		}
	#endif

	if (in_button_cycle)
	{
		if (micros() - last_clock_toggle > BUTTON_LATCH_INTERVAL)
		{
			if (button_cycle > 1)
			{
				int abs_num = button_cycle - 2;
				int col = abs_num % 8;
				if (col<5)
				{
					int row = abs_num / 8;
					int button_num = row * NUM_BUTTON_COLS + col;
					int sense = digitalRead(PIN_BTN_SENSE);

					if (col<5)
						cur_button_state[button_num] = sense;
					#if DEBUG_SLOW
						display(0,"READ cycle(%2d) abs(%2d) row(%d) col(%d) button(%d) state == %s",
							button_cycle,
							abs_num,
							row,
							col,
							button_num,
							sense ? "PRESSED" : "");
					#else
						if (sense)
							display(0,"READ cycle(%2d) abs(%2d) row(%d) col(%d) button(%d) state == %s",
								button_cycle,
								abs_num,
								row,
								col,
								button_num,
								sense ? "PRESSED" : "");
					#endif

					#if DEBUG_SLOW
						if (button_num == 9)
					#else
						if (button_num == 24)
					#endif
					{
						in_button_cycle = 0;
					}
				}
			}
			
			if (in_button_cycle)	// slight optimization to check if cycle ended
			{
				button_cycle++;

				digitalWrite(PIN_BTN_CLK,1);
				#if DEBUG_SLOW
					display(0,"HIGH(%d)",button_cycle);
				#endif
				delayMicroseconds(BUTTON_LATCH_INTERVAL);
				digitalWrite(PIN_BTN_CLK,0);
				#if DEBUG_SLOW
					display(0," LOW(%d)",button_cycle);
				#endif
				last_clock_toggle =  micros();;
			}
		}
	}
	else
	{
		uint32_t now_ms = millis();
		if (now_ms - last_button_cycle >= BUTTON_CYCLE_INTERVAL)
		{
			#if DEBUG_SLOW
				display(0,"-------------------------",0);
			#endif

			last_button_cycle = now_ms;
			in_button_cycle = 1;
			button_cycle = 0;

			digitalWrite(PIN_BTN_CLK,0);	// this line 'fixed' the SMT problem
			digitalWrite(PIN_BTN_DIN,1);
			digitalWrite(PIN_BTN_CLK,1);
			#if DEBUG_SLOW
				display(0,"HIGH(%d)",button_cycle);
			#endif
			delayMicroseconds(BUTTON_LATCH_INTERVAL);
			digitalWrite(PIN_BTN_CLK,0);
			digitalWrite(PIN_BTN_DIN,0);
			#if DEBUG_SLOW
				display(0," LOW(%d)",button_cycle);
			#endif

			last_clock_toggle = micros();
		}
	}
}




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

    //                         handleSerial();
    // delay(1);

	send595bit();


	#if 0

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

		//-------------------------------------------
		// RAW BUTTON IO
		//-------------------------------------------

		static int button_num = -1;
		static bool cur_button_state[NUM_BUTTONS];		// contantly updated

		#define LATCH_DELAY		50			// us
		#define BTN_READ_TIME	0			// every ms

		static uint32_t btn_read_time = 0;
		uint32_t now = millis();
		if (now - btn_read_time > BTN_READ_TIME)
		{
			btn_read_time = now;

			// the clock is always left LOW be
			if (button_num == -1)	// starting new cycle
			{
				bit_num = 0;

				digitalWrite(PIN_BTN_DIN,1);
				digitalWrite(PIN_BTN_CLK,1);		// 0 = 1 goes into the shift register
				delayMicroseconds(LATCH_DELAY);
				digitalWrite(PIN_BTN_CLK,0);
				digitalWrite(PIN_BTN_DIN,0);

				delayMicroseconds(LATCH_DELAY);
				digitalWrite(PIN_BTN_CLK,1);		// 1 = 0 goes into shift register 1 goes to output A
				delayMicroseconds(LATCH_DELAY);
				digitalWrite(PIN_BTN_CLK,0);

				delayMicroseconds(LATCH_DELAY);
				digitalWrite(PIN_BTN_CLK,1);		// 2 = 0 goes into shift register 1 goes to output B
				delayMicroseconds(LATCH_DELAY);
				digitalWrite(PIN_BTN_CLK,0);

				button_num++;						// there will be almost 1 full ms before we read button zero
			}
			else
			{
				cur_button_state[button_num] = digitalRead(PIN_BTN_SENSE);
				// display(dbg_buttons+1,"button_num[%d] = %d",button_num,cur_button_state[button_num]);

				// 3,4,5,6,7

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

	#endif


	//-------------------------------------------
	// PROCESS BUTTON CHANGES
	//-------------------------------------------
	// this will be done by a non-time critical process

	#define dbg_buttons 		0

	#define PROTO_0_LEFT_BNUM		0		// portB on first prototype row_board
	#define PROTO_0_RIGHT_BNUM		4		// portF on first prototype row_board
	#define PROTO_1_LEFT_BNUM		7		// portD on second prototype row_board
	#define PROTO_1_RIGHT_BNUM		8		// portE on second prototype row_board

	
	static bool prev_button_state[NUM_BUTTONS];		// handled by event handler of some kind

	for (int num=0; num<NUM_BUTTONS; num++)
	{
		bool state = cur_button_state[num];
		if (prev_button_state[num] != state)
		{
			prev_button_state[num] = state;
			display(dbg_buttons,"BUTTON_NUM[%d] changed to %d",num,state);

			int led_num =
				num == PROTO_0_LEFT_BNUM ? 0 :
				num == PROTO_0_RIGHT_BNUM ? 1 :
				num == PROTO_1_LEFT_BNUM ? 2 :
				num == PROTO_1_RIGHT_BNUM ? 3 :
				-1;

			if (led_num >= 0)
			{
				setLED(led_num,state?LED_BLUE:LED_BLACK);
				showLEDs();
			}
		}
	}	// process the buttons



}	// loop()


// end of TE3.ino
