//-----------------------------------------
// te3_tft.cpp
//-----------------------------------------

#include "te3_tft.h"
#include <myDebug.h>


ILI9488_t3 tft(
    PIN_TFT_CS,
    PIN_TFT_DC,
    255,            // no RST
    PIN_TFT_MOSI,
    PIN_TFT_SCLK,
    PIN_TFT_MISO);


void init_te3_tft()
{
    display(0,"init_te3_tft()",0);
    
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLUE);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(3);
    tft.print("THERES NO SIMPLE PRINT STRING FUNCTION");
}
