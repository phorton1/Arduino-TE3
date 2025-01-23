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


//---------------------------------------------
// setup
//---------------------------------------------

void setup()
{
    // setColorString(COLOR_CONST_DEFAULT, "\033[94m");  // example for bright blue
        // TE3's normal (default) display color is green
        // TE3_hubs normal display color is bright blue
        // Looper's normal display color, is cyan

	USB_SERIAL_PORT.begin(115200);

	delay(500);
    display(0,"TE3.ino setup() started",0);
	HUB_SERIAL_PORT.begin(115200);

    #if PIN_LED_ALIVE
		pinMode(PIN_LED_ALIVE,OUTPUT);
        digitalWrite(PIN_LED_ALIVE,0);
    #endif

    #if WITH_ROTARIES
        rotaryBoard::begin(PIN_ROTARY_INTERRUPT);
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
