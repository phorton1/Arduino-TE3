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

#if WITH_ROTARIES
    #include "src/rotaryBoard.h"
#endif

#if WITH_MIDI_HOST	// defined in midiHost.h
    #include "src/midiHost.h"
#endif


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
		// calls setUSBSerialNum() in _usbNames.c
		// before staring USB device
		
	USB_SERIAL_PORT.begin(115200);

	delay(500);
    display(0,"TE3.ino setup(%s) started",getUSBSerialNum());
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



//-------------------------------------------------
// button handler (to be moved to te3_buttons.cpp)
//-------------------------------------------------


static bool cur_button_state[NUM_BUTTONS];		// contantly updated


void send595bit()
	// takes at most 1 us plus a little
	//
	//  OH' (portH prime) that is forwarded to the next chip
	//	ACTUALLY goes high at the same time as portG, not portH
	//	as one might expect.
{
	// DIP16 vs SMT chips on breadboard issue
	//
	//	On the DIP16 chips it works as I originally designed it.
	//	However, with the SMT chips there was an anomoly that
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
		//		the 2nd cycle.
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
					cur_button_state[button_num] = digitalRead(PIN_BTN_SENSE);

					#if DEBUG_SLOW
						display(0,"READ cycle(%2d) abs(%2d) row(%d) col(%d) button(%d) state == %s",
							button_cycle,
							abs_num,
							row,
							col,
							button_num,
							cur_button_state[button_num] ? "PRESSED" : "");
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
				last_clock_toggle =  micros();
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

    #if !DEBUG_SLOW
		handleSerial();
		// delay(1);	// not sure if this is needed
	#endif

	send595bit();


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
