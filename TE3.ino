//-------------------------------------------
// TE3.ino
//-------------------------------------------

#include <myDebug.h>

#define FLASH_PIN  2

#define WITH_HUB_SERIAL 1

#define WITH_ROTARY_BOARD  0




#if WITH_HUB_SERIAL
    #if defined(ESP32)

        #define USE_ESP32_HARDWARE_SERIAL 1

        #if USE_ESP32_HARDWARE_SERIAL

            #include <HardwareSerial.h>
            #define HUB_SERIAL_RX   27
            #define HUB_SERIAL_TX   26
            HardwareSerial HUB_SERIAL(1);
                // define a Serial for UART1
        #else

            #define HUB_SERIAL Serial1

        #endif

    #else
    #endif
#endif




#if WITH_ROTARY_BOARD
    #include "rotaryBoard.h"
    static uint8_t last_rot[NUM_ROTARIES];
    #define PIN_ROTARY_INTERRUPT   22
#endif



void setup()
{
    // delay(1000);

    // setColorString(COLOR_CONST_DEFAULT, "\033[94m");  // example for bright blue
        // TE3's normal (default) display color is green
        // TE3_hubs normal display color is bright blue
        // Looper's normal display color, is cyan, I think


    Serial.begin(115200);
    delay(1000);
    display(0,"TE3.ino setup() started",0);

    #if WITH_HUB_SERIAL
        #if defined(ESP32)
            #if USE_ESP32_HARDWARE_SERIAL
                HUB_SERIAL.begin(115200, SERIAL_8N1, HUB_SERIAL_RX, HUB_SERIAL_TX);
            #else
                HUB_SERIAL.begin(115200);
            #endif
        #else
        #endif
    #endif

    pinMode(FLASH_PIN,OUTPUT);
    digitalWrite(FLASH_PIN,0);
    
    // dbgSerial = &Serial;

    #if WITH_ROTARY_BOARD
        rotaryBoard::begin(PIN_ROTARY_INTERRUPT);
    #endif

    display(0,"TE3.ino setup() finished",0);
}




void loop()
{
    static bool flash_on = 0;
    static uint32_t flash_last = 0;
    uint32_t now = millis();
    if (now > flash_last + 250)
    {
        flash_last = now;
        flash_on = !flash_on;
        digitalWrite(FLASH_PIN,flash_on); 
    }
    
    #if WITH_ROTARY_BOARD
        handleRotaries();
    #endif


    #if WITH_HUB_SERIAL
        #define MAX_STRING  250

        static int len = 0;
        static char buf[MAX_STRING+1];

        if (HUB_SERIAL.available())
        {
            char c = HUB_SERIAL.read();
            if (c == 0x0A)
            {
                buf[len++] = 0;
                Serial.println(buf);
                len = 0;
            }
            else if (c != 0x0D && len < MAX_STRING)
            {
                buf[len++] = c;
            }
        }
    #endif
    
    delay(1);
}






#if WITH_ROTARY_BOARD

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

#endif  // WITH_ROTARY_BOARD




// end of TE3.ino
