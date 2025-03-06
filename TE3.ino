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



#define WITH_SCREEN		1
#define WITH_ROTARIES	1


#include "src/defines.h"
#include <myDebug.h>
#include "src/te3_leds.h"
#include "src/commonDefines.h"		// Looper defines
#include "src/iPadDefines.h"		// SampleTank, Tonestack, etc

#if WITH_SCREEN
	#include "src/te3_tft.h"
#endif

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



//-------------------------------------------------
// TE3_BUSY led functions externed in defines.h
//-------------------------------------------------
// used in te3_serial.cpp

static bool flash_on = 0;
static uint32_t flash_last = 0;
static uint32_t te3_busy_led_time = 0;

void setTE3Busy()
{
	digitalWrite(PIN_LED_T3_BUSY,1);
	te3_busy_led_time = millis();
}
void clearTE3Busy()
{
	if (!flash_on && te3_busy_led_time && millis() - te3_busy_led_time > 200)
	{
		te3_busy_led_time = 0;
		digitalWrite(PIN_LED_T3_BUSY,0);
	}
}



//---------------------------------------------
// setup
//---------------------------------------------

void setup()
{
	pinMode(PIN_LED_T3_BUSY,OUTPUT);
	digitalWrite(PIN_LED_T3_BUSY,1);

	for (int i=0; i<23; i++)
	{
		digitalWrite(PIN_LED_T3_BUSY,i&1);
		delay(40);
	}

	#if USE_DBG_SERIAL_PORT
		DBG_SERIAL_PORT.begin(115200);
		DBG_SERIAL_PORT.println("TE3 Debug Serial port output");
		extraSerial = &DBG_SERIAL_PORT;
	#endif

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

	digitalWrite(PIN_LED_T3_BUSY,1);

	delay(500);
    display(0,"TE3.ino setup(%s) started",getUSBSerialNum());

	#if WITH_SCREEN
		init_te3_tft();
	#endif
	
	HUB_SERIAL_PORT.begin(115200);
	RPI_SERIAL_PORT.begin(115200);		// 460800);	// 115200);
		// grumble; apparently the bootloader on the current SD
		// 		card is running at 460800,
		// even tho the bootloader AND the std_kernel used by
		// the Looper, as well as teensyPiLooper were all
		// checked in at 115200!!
		// I'm gonna try updating the boot loader on that SD card

	digitalWrite(PIN_LED_T3_BUSY,0);


	//----------------------------------
	// flash LEDS
	//----------------------------------

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

	//----------------------------------
	// setup for row_boards
	//----------------------------------
	// start the WS2812's and set the 595 pinModes

    initLEDs();
    LEDFancyStart();

	#if 1
		pinMode(PIN_BTN_CLK,OUTPUT);
		pinMode(PIN_BTN_DIN,OUTPUT);
		digitalWrite(PIN_BTN_CLK,0);
			// initial master clock is LOW for 1st prototype board
			// but will be HIGH for actual inverting board
		digitalWrite(PIN_BTN_DIN,0);
		pinMode(PIN_BTN_SENSE,INPUT_PULLDOWN);
	#endif


	//--------------------------------------------
	// final pinModes for rPi Rotaries, Pedals, etc
	//--------------------------------------------
	// may want rPI pinModes earlier and/or to automaticaly
	// reboot pi on TE3 restarts

	pinMode(PIN_SENSE_RPI_RUN,INPUT);
	pinMode(PIN_SENSE_RPI_READY,INPUT_PULLDOWN);
	digitalWrite(PIN_RPI_BOOT,0);	// DONT REBOOT PI automatically!
	pinMode(PIN_RPI_BOOT,OUTPUT);


    #if WITH_ROTARIES
        rotaryBoard::begin(PIN_ROTARY_INTERRUPT);
    #endif


    display(0,"TE3.ino setup() finished",0);
}




//--------------------------------------
// rotary board prototype code
//--------------------------------------

#if WITH_ROTARIES

    void handleRotaries()
    {
		#define DEBOUNCE_TIME	6	// ms

		static uint8_t last_rot[NUM_ROTARIES];
		static bool last_button[NUM_ROTARIES];
		static uint32_t bounce_time = 0;
		uint32_t now = millis();
		if (now - bounce_time < DEBOUNCE_TIME)
			return;

        bool changed = false;
        for (int i=0; i<NUM_ROTARIES; i++)
        {
            uint8_t val = rotaryBoard::getValue(i);
            if (last_rot[i] != val)
            {
                changed = 1;
                last_rot[i] = val;
            }

			bool pressed = rotaryBoard::getRawButton(i);
			if (last_button[i] != pressed)
			{
				changed = 1;
				last_button[i] = pressed;
			}
        }

        if (changed)
            display(0,"rotaries:  %-3d  %-3d  %-3d  %-3d  buttons: %d %d %d %d",
                last_rot[0],
                last_rot[1],
                last_rot[2],
                last_rot[3],
				last_button[0],
				last_button[1],
				last_button[2],
				last_button[3]);
    }

#endif



//-------------------------------------------------
// row_button (74HC595) prototype handler
//-------------------------------------------------

static bool cur_button_state[NUM_BUTTONS];		// contantly updated

#if 1	// NEW

	// alternative implementation
	// entirely polls one button per cycle
	// was written while trying to debug what turned out
	// to be a bad solder joint on the button DOUT on board $4

	// However it is arguably simpler and does not take much time.

	void poll_row_buttons()
	{
		#define BUTTON_CYCLE_INTERVAL		33				// ms
		#define BUTTON_POLL_INTERVAL		1				// us between polls
		#define BUTTON_LATCH_DELAY			1				// us between clock up/down

		static int button_cycle = 0;
		static bool in_button_cycle = 0;
		static uint32_t last_button_cycle = 0;		// ms timer
		static uint32_t last_button_poll = 0;		// us timer

		if (in_button_cycle)
		{
			if (micros() - last_button_poll > BUTTON_POLL_INTERVAL)
			{
				// don't need to do last two latches
				if (button_cycle == NUM_BUTTON_ROWS * 8 - 2)
				{
					in_button_cycle = 0;	// finished
				}
				else
				{
					digitalWrite(PIN_BTN_CLK,1);
					delayMicroseconds(BUTTON_LATCH_DELAY);
					digitalWrite(PIN_BTN_CLK,0);

					int col = (button_cycle % 8) - 1;
					if (col >= 0 && col <= NUM_BUTTON_COLS)
					{
						delayMicroseconds(BUTTON_LATCH_DELAY);

						int row = button_cycle / 8;
						int button_num = row * NUM_BUTTON_COLS + col;
						cur_button_state[button_num] = digitalRead(PIN_BTN_SENSE);
					}	// valid button

					last_button_poll = micros();
					button_cycle++;

				}	// still polling
			}	// time to do a poll
		} 	// in_button_cyckle

		else	// time to start new cycle?
		{
			uint32_t now_ms = millis();
			if (!last_button_cycle || (now_ms - last_button_cycle >= BUTTON_CYCLE_INTERVAL))
			{
				last_button_cycle = now_ms;
				in_button_cycle = 1;
				button_cycle = 0;

				// latch the 1 into the first 595

				digitalWrite(PIN_BTN_CLK,0);	// this line 'fixed' the SMT problem
				digitalWrite(PIN_BTN_DIN,1);
				digitalWrite(PIN_BTN_CLK,1);
				delayMicroseconds(BUTTON_LATCH_DELAY);
				digitalWrite(PIN_BTN_CLK,0);
				digitalWrite(PIN_BTN_DIN,0);
				#if DEBUG_SLOW
					display(0," LOW(%d)",button_cycle);
				#endif

				last_button_poll = micros();
			}	// start new cycle
		}	// check if time to start new cycle
	}	// poll_row_buttons()

#else 	// OLD

	void poll_row_buttons()
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

#endif 	// OLD



//--------------------------
// sendTestMidi()
//--------------------------

static void sendTestMidi(int num)
{
	#define PORT_USB 	1
	#define PORT_RPI 	2
	#define PORT_HUB    3

	uint8_t port = 0;
	uint8_t channel = 0;
	uint8_t cc_num = 0;
	uint8_t value = 0;

	/// with USB midi

	if (num == 0) 		// turn guitar distortion on/off
	{
		port = PORT_USB;
		channel = GUITAR_EFFECTS_CHANNEL;
		cc_num = GUITAR_DISTORTION_EFFECT_CC;
		static uint8_t effect_state = 0x00;
		effect_state = effect_state ? 0 : 0x7f;
		value = effect_state;
	}
	else if (num == 1)	// press Looper Track1 button
	{
		port = PORT_RPI;
		cc_num = LOOP_COMMAND_CC;
		value = LOOP_COMMAND_TRACK_BASE + 0;
	}
	else if (num == 2)	// clear the Looper
	{
		port = PORT_RPI;
		cc_num = LOOP_COMMAND_CC;
		value = LOOP_COMMAND_CLEAR_ALL;
	}

	if (port == PORT_USB)
	{
		display(0,"Sending USB MIDI channel(%d) cc(%02x) value(%02x)",channel,cc_num,value);
		usbMIDI.sendControlChange(cc_num, value, channel);
	}
	else if (port)
	{
		uint8_t msg[4];
		msg[0] = 0x0b;
		msg[1] = 0xb0;
		msg[2] = cc_num;
		msg[3] = value;

		display(0,"Sending %s SERIAL MIDI cc(%02x) value(%02x)",
			port == PORT_RPI ? "RPI" : "HUB",cc_num,value);

		Stream *out = port == PORT_RPI ? &RPI_SERIAL_PORT : &HUB_SERIAL_PORT;
		out->write(msg,4);
	}
	

}



//==========================================================================
// loop()
//==========================================================================

void loop()
{
	uint32_t led_delay = flash_on ? 20 : 1980;
	uint32_t flash_now = millis();
	if (flash_now - flash_last > led_delay)
	{
		flash_last = flash_now;
		flash_on = !flash_on;
		digitalWrite(PIN_LED_T3_BUSY,flash_on);
	}

    #if WITH_ROTARIES
        handleRotaries();
    #endif

    #if 1
		handleSerial();
	#endif



	//-------------------------------------------
	// prototype row_button handling
	//-------------------------------------------

	poll_row_buttons();
		// POLL THE ROW_BUTTONS OFTEN

	#define dbg_buttons 		0

	static bool prev_button_state[NUM_BUTTONS];		// handled by event handler of some kind

	for (int num=0; num<NUM_BUTTONS; num++)
	{
		bool state = cur_button_state[num];
		if (prev_button_state[num] != state)
		{
			prev_button_state[num] = state;
			// display(dbg_buttons,"BUTTON_NUM[%d] changed to %d",num,state);

			if (state)
				sendTestMidi(num);

			setLED(num,state?LED_BLUE:LED_BLACK);
			showLEDs();

		}
	}	// process the buttons


	//--------------------------------------------
	// handle rPI state changes (LEDS)
	//--------------------------------------------

	static int rpi_running = -1;
	static int rpi_ready = -1;

	int r_running = digitalRead(PIN_SENSE_RPI_RUN) ? 1 : 0;
	int r_ready = digitalRead(PIN_SENSE_RPI_READY) ? 1 : 0;

	if (rpi_running != r_running)
	{
		rpi_running = r_running;
		display(0,"RPI%s RUNNING",rpi_running?"":" NOT");
		analogWrite(PIN_LED_RPI_RUN,rpi_running * 50); // PWM brightness
	}
	if (rpi_ready != r_ready)
	{
		rpi_ready = r_ready;
		display(0,"RPI%s READY",rpi_ready?"":" NOT");
		analogWrite(PIN_LED_RPI_READY,rpi_ready * 128);	// PWM brightness
	}


}	// loop()


// end of TE3.ino
