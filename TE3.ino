//-------------------------------------------
// TE3.ino
//-------------------------------------------

#include <myDebug.h>
#include "serial.h"

#define FLASH_PIN  2

#define WITH_ROTARY_BOARD  0


//--------------------------------------
// rotary board
//--------------------------------------

#if WITH_ROTARY_BOARD

    #include "src/rotaryBoard.h"
    static uint8_t last_rot[NUM_ROTARIES];
    #define PIN_ROTARY_INTERRUPT   22

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
// setup
//---------------------------------------------

void setup()
{
    init_serial();
    display(0,"TE3.ino setup() started",0);

    #if FLASH_PIN
        pinMode(FLASH_PIN,OUTPUT);
        digitalWrite(FLASH_PIN,0);
    #endif

    #if WITH_ROTARY_BOARD
        rotaryBoard::begin(PIN_ROTARY_INTERRUPT);
    #endif

    display(0,"TE3.ino setup() finished",0);
}



//---------------------------------------------
// loop()
//---------------------------------------------

void loop()
{
    #if FLASH_PIN
        static bool flash_on = 0;
        static uint32_t flash_last = 0;
        uint32_t flash_now = millis();
        if (flash_now > flash_last + 250)
        {
            flash_last = flash_now;
            flash_on = !flash_on;
            digitalWrite(FLASH_PIN,flash_on);
        }
    #endif

    #if WITH_ROTARY_BOARD
        handleRotaries();
    #endif

    testSerialImplementation();

    delay(1);
}



// end of TE3.ino
