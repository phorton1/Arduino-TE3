//-------------------------------------------
// TE3.ino
//-------------------------------------------

#include <myDebug.h>

#define WITH_ROTARY_BOARD  1

#if WITH_ROTARY_BOARD
    #include "rotaryBoard.h"
    static uint8_t last_rot[NUM_ROTARIES];
#endif


// teensy 4.x pin reminders
// #define PIN_SDA     18
// #define PIN_SCL     19

#define PIN_ROTARY_INTERRUPT   22




void setup()
{
    Serial.begin(115200);
    delay(500);
    display(0,"TE3.ino setup() started",0);

    #if WITH_ROTARY_BOARD
        rotaryBoard::begin(PIN_ROTARY_INTERRUPT);
    #endif

    display(0,"TE3.ino setup() finished",0);
}


void loop()
{
    #if WITH_ROTARY_BOARD
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

    #endif
}
