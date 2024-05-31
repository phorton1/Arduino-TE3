//-------------------------------------------
// TE3.ino
//-------------------------------------------

#include <myDebug.h>
#include "serial.h"

#define FLASH_PIN  2

#define WITH_ROTARY_BOARD  0


#define SERIAL_ISOLATION_TEST	0   // 25
	// A pin for testing the ESP32 serial opto-isolator.
	// The program will generate a square wave signal on this pin.
#define ISOLATION_FREQ          100000
    // frequency for the square weave

#if SERIAL_ISOLATION_TEST
	#include <driver/ledc.h>
#endif




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

    #if SERIAL_ISOLATION_TEST
    
        ledc_timer_config_t ledc_timer;
        ledc_channel_config_t ledc_channel;

        ledc_timer.speed_mode = LEDC_HIGH_SPEED_MODE;
        ledc_timer.bit_num    = LEDC_TIMER_2_BIT;
        ledc_timer.timer_num  = LEDC_TIMER_1;
        ledc_timer.freq_hz    = 2048000;

        ledc_channel.gpio_num   = SERIAL_ISOLATION_TEST;    // GPIO_NUM_33,
        ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
        ledc_channel.channel    = LEDC_CHANNEL_0;
        ledc_channel.timer_sel  = LEDC_TIMER_1;
        ledc_channel.duty       = 2;

        ledc_timer_config(&ledc_timer);
        ledc_channel_config(&ledc_channel);

        uint32_t before_freq = ledc_get_freq(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_1);
        int rslt = ledc_set_freq(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_1, ISOLATION_FREQ);
        delay(100);
        uint32_t after_freq = ledc_get_freq(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_1);
        display(0,"SERIAL_ISOLATION_TEST(%d) before(%u) after(%u) rslt(%d)",
            SERIAL_ISOLATION_TEST,
            before_freq,
            after_freq,
            rslt);
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
