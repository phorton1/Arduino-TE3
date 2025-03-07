//------------------------------------
// te3_screen.h
//------------------------------------

#pragma once

#include <ILI9488_t3.h>
#include <ILI9488_t3_font_Arial.h>
#include <ILI9488_t3_font_ArialBold.h>
#include "defines.h"    // for int_rect


#define TFT_WIDTH           480
#define TFT_HEIGHT          320

// these color constants are the same whether using
// myLCD, ILI9486_t3, or ILI9341_t3

#define TFT_RGB_COLOR(r,g,b)  ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

#define TFT_BLACK           0x0000
#define TFT_BLUE            0x001F
#define TFT_RED             0xF800
#define TFT_GREEN           0x07E0
#define TFT_CYAN            0x07FF
#define TFT_MAGENTA         0xF81F
#define TFT_YELLOW          0xFFE0
#define TFT_WHITE           0xFFFF

#define TFT_NAVY            0x000F
#define TFT_DARKGREEN       0x03E0
#define TFT_DARKCYAN        0x03EF
#define TFT_MAROON          0x7800
#define TFT_PURPLE          0x780F
#define TFT_OLIVE           0x7BE0
#define TFT_LIGHTGREY       0xC618
#define TFT_DARKGREY        0x7BEF
#define TFT_ORANGE          0xFD20
#define TFT_GREENYELLOW     0xAFE5
#define TFT_PINK            0xF81F


#define LCD_JUST_LEFT    0
#define LCD_JUST_CENTER  1
#define LCD_JUST_RIGHT   2


class TE3_TFT : public ILI9488_t3
    // derived so that we can get to protected
    // charBounds() method for justified printing
{
    public:

        TE3_TFT(uint8_t _CS, uint8_t _DC, uint8_t _RST = 255, uint8_t _MOSI=255, uint8_t _SCLK=255, uint8_t _MISO=255);

        void init();

        void fillIntRect(int_rect &rect, uint16_t color);
        void drawBorder(int x, int y, int w, int h, int b, uint16_t color);

        void printfJustified(
            int x,
            int y,
            int w,
            int h,
            int just,
            uint16_t fc,
            uint16_t bc,
            bool use_bc,
            const char *format,
            ...);
        void printfvJustified(
            int x,
            int y,
            int w,
            int h,
            int just,
            uint16_t fc,
            uint16_t bc,
            bool use_bc,
            const char *format,
            va_list args);
        void printJustified(
            int x,
            int y,
            int w,
            int h,
            int just,
            uint16_t fc,
            uint16_t bc,
            bool use_bc,
            const char *text);

};  // TE3_TFT


extern TE3_TFT tft;
