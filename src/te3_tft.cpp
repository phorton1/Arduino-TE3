//-----------------------------------------
// te3_tft.cpp
//-----------------------------------------

#include "te3_tft.h"
#include <myDebug.h>


#define dbg_la		1

#define DEBUG_DRAW_FONT_CHAR   0

#define MAX_PRINT_LEN  1023
	// 1k buffer on the stack!!
	// Note that var-arg formats can only be half of this ?!?
    

TE3_TFT tft(
    PIN_TFT_CS,
    PIN_TFT_DC,
    255,            // no RST
    PIN_TFT_MOSI,
    PIN_TFT_SCLK,
    PIN_TFT_MISO);


TE3_TFT::TE3_TFT(uint8_t _CS, uint8_t _DC, uint8_t _RST, uint8_t _MOSI, uint8_t _SCLK, uint8_t _MISO) :
    ILI9488_t3(_CS,_DC,_RST,_MOSI,_SCLK,_MISO)
{}



void TE3_TFT::init()
{
    display(0,"TE3_TFT::init()",0);
    
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    #if 0   // bug demonstration
        delay(5000);
        display(0,"calling drawString() fails with no font",0);
        // but if I include the following line it survives
        // tft.setFont(Arial_10);
        tft.setDefaultFont();
        tft.setTextSize(2);
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.drawString("THIS FAILS UNLESS I SET A FONT",0,150);
        delay(10000);
    #endif
}


void TE3_TFT::fillIntRect(int_rect &rect, uint16_t color)
{
    tft.fillRect(
        rect.xs,
        rect.ys,
        rect.width(),
        rect.height(),
        color);
}


void TE3_TFT::drawBorder(int x, int y, int w, int h, int b, uint16_t color)
	// draw a frigin border
{
	tft.fillRect(x,		y,		b,		h,	color);
	tft.fillRect(x+w-b,	y,		b,		h,	color);
	tft.fillRect(x,		y,		w,		b,	color);
	tft.fillRect(x,		y+h-b,	w,		b,	color);
}



void TE3_TFT::printfJustified(
	int x,
	int y,
	int w,
	int h,
	int just,
	uint16_t fc,
	uint16_t bc,
	bool use_bc,
	const char *format,
	...)
{
	va_list args;
	va_start(args, format);
	printfvJustified(x,y,w,h,just,fc,bc,use_bc,format,args);
}


void TE3_TFT::printfvJustified(
	int x,
	int y,
	int w,
	int h,
	int just,
	uint16_t fc,
	uint16_t bc,
	bool use_bc,
	const char *format,
	va_list args)
{
	char display_buffer[MAX_PRINT_LEN+1];
	if (strlen(format) >= MAX_PRINT_LEN/2)
	{
		my_error("error - MAX_PRINT_LEN overflow",0);
		return;
	}
	vsprintf(display_buffer,format,args);
	printJustified(x,y,w,h,just,fc,bc,use_bc,display_buffer);
}


void TE3_TFT::printJustified(
	int x,
	int start_y,
	int width,
	int height,
	int just,
	uint16_t fc,
	uint16_t bc,
	bool use_bc,
	const char *text)
{
	// prints \n delimited lines

	char cut_buf[MAX_PRINT_LEN+1];
		// another 1K buffer on the stack, just so that we can
		// we can break the passed in string into lines at \n's
		// for calling drawString ...

	display(dbg_la,"printJustified(%d,%d,%d,%d,  %d, 0x%04x, 0x%04x, %d, \"%s\")", x, start_y, width, height, just, fc, bc, use_bc, text);

	tft.setTextColor(fc);
	if (use_bc)
		tft.fillRect(x,start_y,width,height,bc);

	int y = start_y + 1;
	int yoffset;    // paul missing implementation of tft.getTextSizeY();

    if (font)
        yoffset = font->line_space;
    else if (gfxFont)
        yoffset = 8 * gfxFont->yAdvance;
    else
        yoffset = 8 * textsize_y * 8;

    // Will do it's best to print whole words on a line.
    // If at least a single whole word wont fit,
    //      the part of the word that will fit will be
    // 		printed and the word will be continued on the next line
    // If at least one word has been printed
    //    will push full words to the next line skipping leading whitespace

    while (*text && y < start_y + height - 1) // while the top of the next line is in the rectangle
	{
		int len = 0;
		int word_len = 0;
		int pixel_len = 0;
		int word_pixel_len = 0;
		const char *word = 0;

		while (*text && len < MAX_PRINT_LEN)
		{
			char c = *text;

            // int pix = 16;   // undefined: tft.getTextSizeX();   // getCharWidth(c);
            // have to call this exceedingly complicated uncommented method with ILI9488_t3.h when
            // all we simply want is the character width in pixels in the current font setting

            int16_t pix = 0;    // pault missing implementation tft.getTextSizeX();
            int16_t unused_y, unused_minx, unused_miny, unused_maxx, ununsed_maxy;
            charBounds(c, &pix, &unused_y, &unused_minx, &unused_miny, &unused_maxx, &ununsed_maxy);
            
			if (c == '\n')
			{
				text++;
				break;
			}
			else if (pixel_len + pix > width)
			{
				// unable to fit a single full word on the line

				if (!word)
					break;

				// othewise, write the full word
				// and set the pointer to the next word

				len = word_len;
				pixel_len = word_pixel_len;
				text = word;
				break;
			}
			else if (c == ' ')
			{
				// a space ends a word
				// and leaves word pointing after the space

				word_len = len;
				word_pixel_len = pixel_len;
				word = text + 1;
			}

			text++;
			pixel_len += pix;
			cut_buf[len++] = c;

		}	// inner while *text

		cut_buf[len++] = 0;

		int use_x = x;
		if (just != LCD_JUST_LEFT)
		{
			int xoffset = (width - pixel_len);
			if (xoffset < 0) xoffset = 0;
			if (just == LCD_JUST_CENTER)
				xoffset /= 2;
			use_x += xoffset;
		}

		tft.drawString(cut_buf,use_x,y);
		y += yoffset;

	}	// outer while *text
}





