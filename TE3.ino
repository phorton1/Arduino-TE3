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

#include <myDebug.h>
#include "src/prefs.h"
#include "src/te3_tft.h"
#include "src/te3_leds.h"
#include "src/buttons.h"
#include "src/pedals.h"
#include "src/te3_rotaries.h"
#include "src/expSystem.h"
#include "src/midiHost.h"
#include "src/fileSystem.h"



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
// Stream setup
//---------------------------------------------

Stream *TE3_DEBUG_STREAM;
Stream *HUB_DEBUG_OUTPUT;
Stream *RPI_DEBUG_OUTPUT;
Stream *MONITOR_OUTPUT;

static void setOneStream(uint8_t how_follow, int pref, Stream **stream)
{
	uint8_t how = getPref8(pref);
	if (how == SERIAL_DEVICE_FOLLOW)
		how = how_follow;
	*stream =
		how == SERIAL_DEVICE_DBG ? (Stream *) &DBG_SERIAL_PORT :
		how == SERIAL_DEVICE_USB ? (Stream *) &USB_SERIAL_PORT : 0;
}



void initDebugStreams()
	// called after prefs inited and streams are started
	// and when stream preferences change
{
	uint8_t how_follow = getPref8(PREF_FOLLOW_DEVICE);
	setOneStream(how_follow, PREF_TE3_DEBUG_STREAM, &TE3_DEBUG_STREAM);
	setOneStream(how_follow, PREF_HUB_DEBUG_OUTPUT, &HUB_DEBUG_OUTPUT);
	setOneStream(how_follow, PREF_RPI_DEBUG_OUTPUT, &RPI_DEBUG_OUTPUT);
	setOneStream(how_follow, PREF_MONITOR_OUTPUT, &MONITOR_OUTPUT);
	dbgSerial = TE3_DEBUG_STREAM;
}


//---------------------------------------------
// setup
//---------------------------------------------

void setup()
{
	dbgSerial = 0;		// turn off myDebug output

    // setColorString(COLOR_CONST_DEFAULT, "\033[94m");  // example for bright blue
        // TE3's normal (default) display color is green
        // TE3_audio (hub) normal display color is bright blue
        // Looper's normal display color, is cyan for bootloader, or white in Looper

	// quickly flash the busy led to indicate a boot is happening

	pinMode(PIN_LED_T3_BUSY,OUTPUT);
	digitalWrite(PIN_LED_T3_BUSY,1);
	for (int i=0; i<23; i++)
	{
		digitalWrite(PIN_LED_T3_BUSY,i&1);
		delay(40);
	}

	// load the prefs and set how_debug_te3 based on them

    bool prefs_reset = init_global_prefs();
	uint8_t how_follow = getPref8(PREF_FOLLOW_DEVICE);
	uint8_t how_debug_te3 = getPref8(PREF_TE3_DEBUG_STREAM);
	if (how_debug_te3 == SERIAL_DEVICE_FOLLOW)
		how_debug_te3 = how_follow;

	//-----------------------------------
	// start the dbg SERIAL PORT
	//-----------------------------------
	// and assign it to myDebug based on pref

	DBG_SERIAL_PORT.begin(115200);
	delay(200);
	DBG_SERIAL_PORT.println("TE3 DBG_SERIAL_PORT");
	if (how_debug_te3 == SERIAL_DEVICE_DBG)
		dbgSerial = (Stream *) &DBG_SERIAL_PORT;

	// start ourself as a USB device
	// and assign it to myDebug based on pref

    delay(500);
	my_usb_init();
		// calls setUSBSerialNum() in _usbNames.c
		// before staring USB device
	USB_SERIAL_PORT.begin(115200);
	if (how_debug_te3 == SERIAL_DEVICE_USB)
		dbgSerial = (Stream *) &USB_SERIAL_PORT;

	// start the other streams and
	// show the version with myDebug

	delay(500);
	HUB_SERIAL_PORT.begin(115200);
	RPI_SERIAL_PORT.begin(115200);		// 460800);	// 115200);

	const char *version_msg = "teensyExpression " TEENSY_EXPRESSION_VERSION " setup() started ... ";
	display(0,version_msg,0);

	digitalWrite(PIN_LED_T3_BUSY,1);
	initDebugStreams();


	//-----------------------------------
	// start the TFT
	//-----------------------------------
	// and show yellow warning messages as needed

	tft.init();
    tft.setTextColor(TFT_WHITE,TFT_BLACK);
    tft.setFont(Arial_16);
    tft.setCursor(5,5);
    tft.println(version_msg);

    tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    int do_delay = 2000;
    if (prefs_reset)
    {
        const char *msg = "    PREFS WERE AUTOMATICALLY RESET!!";
        warning(0,"%s",msg);
        tft.println(msg);
        do_delay = 5000;
    }

	const char *te3_dbg_output_name =
		how_debug_te3 == SERIAL_DEVICE_OFF ? "OFF" :
		how_debug_te3 == SERIAL_DEVICE_DBG ? "SERIAL PORT" :
		"USB PORT";
	tft.print("    TE3_DEBUG_STREAM IS ");
	tft.println(te3_dbg_output_name);

	digitalWrite(PIN_LED_T3_BUSY,0);

	//-------------------------------------------
	// flash rPi LEDS
	//-------------------------------------------

	digitalWrite(PIN_LED_T3_BUSY,0);

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

	digitalWrite(PIN_LED_T3_BUSY,1);

	//----------------------------------
	// initialize other devices
	//----------------------------------

    initLEDs();
    LEDFancyStart();
	theButtons.init();
	thePedals.init();
	te3_rotaries::init();

	digitalWrite(PIN_LED_T3_BUSY,0);

	//--------------------------------------------
	// final pinModes for rPi
	//--------------------------------------------
	// may want rPI pinModes earlier and/or to automaticaly
	// reboot pi on TE3 restarts

	pinMode(PIN_SENSE_RPI_RUN,INPUT);
	pinMode(PIN_SENSE_RPI_READY,INPUT_PULLDOWN);
	digitalWrite(PIN_RPI_BOOT,0);	// DONT REBOOT PI automatically!
	pinMode(PIN_RPI_BOOT,OUTPUT);

	digitalWrite(PIN_LED_T3_BUSY,1);


    //--------------------------------------
    // start the file system
    //--------------------------------------

	if (!initFileSystem())
	{
        const char *msg = "    COULD NOT START FILE SYSTEM!!";
        my_error("%s",msg);
        tft.println(msg);
        do_delay = 10000;
	}
    else
    {
        tft.setTextColor(TFT_WHITE);
        tft.println("File System Started OK");
    }

	delay(do_delay);
	
	//--------------------------------------------------
	// start the system
	//--------------------------------------------------

	#if WITH_MIDI_HOST
		midi_host.init();
	#endif

	theSystem.begin();
		
	digitalWrite(PIN_LED_T3_BUSY,0);

    display(0,"TE3.ino setup() finished",0);
}




//==========================================================================
// loop()
//==========================================================================
// Does much of what used to be done in the system's lower priority
// "timer_handler" which is now simply handled in loop()


void loop()
{
	handleSerial();
		// in te3_serial.cpp

	theButtons.loop();
	thePedals.loop();
	te3_rotaries::loop();
		// these three moved here from expSystem::timer_handler()

	theSystem.updateUI();


	//---------------------------------------------
	// flash the BUSY Led
	//---------------------------------------------

	uint32_t led_delay = flash_on ? 20 : 1980;
	uint32_t flash_now = millis();
	if (flash_now - flash_last > led_delay)
	{
		flash_last = flash_now;
		flash_on = !flash_on;
		digitalWrite(PIN_LED_T3_BUSY,flash_on);
	}


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
