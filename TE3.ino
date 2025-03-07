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

    bool prefs_reset = init_global_prefs();

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

	tft.init();
    tft.setTextColor(TFT_WHITE,TFT_BLACK);
    tft.setFont(Arial_16);
    tft.setCursor(5,5);
    tft.print("teensyExpression ");
    tft.print(TEENSY_EXPRESSION_VERSION);
    tft.println(" started ... ");

    int do_delay = 2000;
    tft.setTextColor(TFT_YELLOW);

    if (prefs_reset)
    {
        const char *msg = "    PREFS WERE AUTOMATICALLY RESET!!";
        warning(0,"%s",msg);
        tft.println(msg);
        do_delay = 5000;
    }
	
	HUB_SERIAL_PORT.begin(115200);
	RPI_SERIAL_PORT.begin(115200);		// 460800);	// 115200);

	delay(do_delay);
	
	digitalWrite(PIN_LED_T3_BUSY,0);

	//----------------------------------
	// flash rPi LEDS
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
	// setup global handlers
	//----------------------------------

    initLEDs();
    LEDFancyStart();
	theButtons.init();
	thePedals.init();
	te3_rotaries::init();

	//--------------------------------------------
	// final pinModes for rPi
	//--------------------------------------------
	// may want rPI pinModes earlier and/or to automaticaly
	// reboot pi on TE3 restarts

	pinMode(PIN_SENSE_RPI_RUN,INPUT);
	pinMode(PIN_SENSE_RPI_READY,INPUT_PULLDOWN);
	digitalWrite(PIN_RPI_BOOT,0);	// DONT REBOOT PI automatically!
	pinMode(PIN_RPI_BOOT,OUTPUT);

	theSystem.begin();

    display(0,"TE3.ino setup() finished",0);
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

	theSystem.updateUI();

	#if 1
		handleSerial();
	#endif

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
