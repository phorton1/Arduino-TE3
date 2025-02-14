
#include "te3_leds.h"
#include "defines.h"
#include "myDebug.h"

#define USE_ADAFRUIT    0

#if USE_ADAFRUIT
    #include <Adafruit_NeoPixel.h>
#else
    #include <WS2812Serial.h>
#endif

// #include "prefs.h"


//---------------------------------
// LEDS
//---------------------------------
// WS2812Serial library usable pins:
//
//   Teensy LC:   1, 4, 5, 24
//   Teensy 3.2:  1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
//   Teensy 3.5:  1, 5, 8, 10, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 26, 32, 33
//   Teensy 4.x:  20, period.

// in defines.h:  #define PIN_LED_DIN          20
    // Note that choosing to use pin 5 eats up Serial1
    // hence why we have to use Serial3 in teensyExpression.ino
    // Pauls Notes:
    //
    //      Non-blocking performance does come with a cost.  15 bytes of memory are required
    //      per LED, rather than the usual 3 bytes with [FastLED](http://fastled.io/) or
    //      [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel).  One of
    //      the [hardware serial ports](https://www.pjrc.com/teensy/td_uart.html) is also
    //      used to transmit the data, making that port unavailable for other uses.
    //      
    //      ## Supported Pins & Serial Ports
    //      
    //      | Port    | Teensy LC   | Teensy 3.2 | Teensy 3.5 | Teensy 3.6 | Teensy 4.x
    //      | :------ | :---------: | :--------: | :--------: | :--------: | :--------:
    //      | Serial1 | 1, 4, 5, 24 | 1, 5       | 1, 5, 26   | 1, 5, 26   |
    //      | Serial2 |             | 10, 31     | 10         | 10         |
    //      | Serial3 |             | 8          | 8          | 8          |
    //      | Serial4 |             |            | 32         | 32         |
    //      | Serial5 |             |            | 33         | 33         | 20
    //      | Serial6 |             |            | 48         |            |
    //      
    //      Serial2 & Serial3 on Teensy LC are not supported, due to lack of configurable
    //      oversampling needed to run at the high speed required.
    //      
    //      Serial3-Serial6 should be used only with CPU speeds 120 or 180 MHz.
    //      
    //      Serial6 on Teensy 3.6 is not currently supported, due to different hardware
    //      registers.    
    



#if USE_ADAFRUIT
    Adafruit_NeoPixel leds(NUM_BUTTONS,PIN_LED_DIN);
#else
    unsigned drawingMemory[NUM_BUTTONS];
    byte renderingMemory[NUM_BUTTONS*3];         //  3 bytes per LED
    DMAMEM byte displayMemory[NUM_BUTTONS*12]; // 12 bytes per LED
    WS2812Serial leds(NUM_BUTTONS, displayMemory, renderingMemory, PIN_LED_DIN, WS2812_GRB);
#endif


unsigned brightness = 30;
bool leds_changed = 0;

void initLEDs()
{
    display(0,"initLEDs() USE_ADAFRUIT=%d",USE_ADAFRUIT);
    leds.begin();
    #if 1
        for (int i=0; i<5; i++)
        {
            setLED(0,i&1?LED_RED:LED_GREEN);
            setLED(1,i&1?LED_GREEN:LED_RED);
            showLEDs(1);
            delay(200);
        }
        delay(200);
    #endif
    display(0,"initLEDs() finished",0);

    // setLEDBrightness(getPref8(PREF_BRIGHTNESS));
}


int getLEDBrightness()
{
    return brightness;    
}


void setLEDBrightness(int i)   // 0..100
{
    brightness = i;
    showLEDs(true);
}


void setLED(int num, unsigned color)
{
    int row = num / NUM_BUTTON_COLS;
    int col = num % NUM_BUTTON_COLS;
    setLED(row,col,color);
}


void setLED(int row, int col, unsigned color)
    //  0, 1, 2, 3, 4
    //  9, 8, 7, 6, 5
    // 10,11,12,13,14
    // 19,18,17,16,15
    // 20,21,22,23,24
{
    int i;
    if (row & 1)
    {
        i = (row+1) * NUM_BUTTON_COLS - col - 1;
    }
    else
    {
        i = row * NUM_BUTTON_COLS + col; 
    }
    #if USE_ADAFRUIT
        leds.setPixelColor(i,color);
    #else
        drawingMemory[i] = color;
    #endif
    leds_changed = 1;
}



void showLEDs(bool force)
{
    if (force || leds_changed)
    {
        #if !USE_ADAFRUIT
            for (int i=0; i<NUM_BUTTONS; i++)
            {
                unsigned c = drawingMemory[i];
                unsigned r = (c >> 16) * brightness;
                unsigned g = ((c >> 8) & 0xff) * brightness;
                unsigned b = (c & 0xff) * brightness;
                r /= 100;
                g /= 100;
                b /= 100;
                leds.setPixel(i,(r<<16)+(g<<8)+b);
            }
        #endif
        leds.show();
    }
    leds_changed = false;
}



void LEDFancyStart()
{
    for (int row=0; row<NUM_BUTTON_ROWS; row++)
    {
        for (int col=0; col<NUM_BUTTON_COLS; col++)
        {
            float c = col;
            float r = row;

            float red = (c/4) * 255.0;
            float blue = ((4-c)/4) * 255.0;
            float green = (r/4) * 255.0;

            uint32_t rr = red;
            uint32_t gg = green;
            uint32_t bb = blue;

            setLED(row,col,(rr << 16) + (gg << 8) + bb);
            showLEDs();
            delay(40);
        }
    }
    delay(1000);
    clearLEDs();
    showLEDs();
}



void clearLEDs()
{
    for (int row=0; row<NUM_BUTTON_ROWS; row++)
    {
        for (int col=0; col<NUM_BUTTON_COLS; col++)
        {
            setLED(row,col,0);
        }
    }
}