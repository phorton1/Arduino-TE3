//-------------------------------------------
// TE3.ino
//-------------------------------------------

#include "src/defines.h"
#include <myDebug.h>


#ifdef ESP32
	Preferences preferences;
	HardwareSerial HUB_SERIAL_PORT(1);
#endif




//---------------------------------------------
// setup
//---------------------------------------------

void setup()
{
	#ifdef ESP32
		preferences.begin("TE3", false);
	#endif

    // setColorString(COLOR_CONST_DEFAULT, "\033[94m");  // example for bright blue
        // TE3's normal (default) display color is green
        // TE3_hubs normal display color is bright blue
        // Looper's normal display color, is cyan, I think

	#ifdef ESP32
	    USB_SERIAL_PORT.begin(921600);	// ESP32
	#else
		USB_SERIAL_PORT.begin(115200);	// Teensy4.1
	#endif

	delay(500);
    display(0,"TE3.ino setup() started",0);

	#ifdef ESP32
		HUB_SERIAL_PORT.begin(115200, SERIAL_8N1, PIN_HUB_SERIAL_RX, PIN_HUB_SERIAL_TX);
	#else
		HUB_SERIAL_PORT.begin(115200);	// Teensy4.1
	#endif

    #if PIN_LED_ALIVE
        pinMode(PIN_LED_ALIVE,OUTPUT);
        digitalWrite(PIN_LED_ALIVE,0);
    #endif

    #if WITH_ROTARIES
        rotaryBoard::begin(PIN_ROTARY_INTERRUPT);
    #endif


	#ifdef ESP32
		#if WITH_WIFI
			#if WITH_TELNET
				init_telnet();
			#endif

			String ssid = preferences.getString("STA_SSID", "");
			String pass = preferences.getString("STA_PASS", "");
			if (ssid != "" && pass != "")
				connectWifi(ssid,pass);
		#endif
	#endif
	
    display(0,"TE3.ino setup() finished",0);
}




//--------------------------------------
// rotary board
//--------------------------------------

#if WITH_ROTARIES

    #include "src/rotaryBoard.h"
    static uint8_t last_rot[NUM_ROTARIES];

    void handleRotaries()
    {
        rotaryBoard::process();

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
    #if PIN_LED_ALIVE
        static bool flash_on = 0;
        static uint32_t flash_last = 0;
        uint32_t flash_now = millis();
        if (flash_now > flash_last + 250)
        {
            flash_last = flash_now;
            flash_on = !flash_on;
            digitalWrite(PIN_LED_ALIVE,flash_on);
        }
    #endif

    #if WITH_ROTARIES
        handleRotaries();
    #endif

    handleSerial();

    delay(1);
}



// end of TE3.ino
