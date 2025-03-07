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
    tft.fillScreen(TFT_BLACK);
    // tft.setTextColor(TFT_WHITE);
    // tft.setTextSize(3);
    // tft.print("THERES NO SIMPLE PRINT STRING FUNCTION");
}





// extern
void fillRect(int_rect &rect, int color)
{
    tft.fillRect(
        rect.xs,
        rect.ys,
        rect.width(),
        rect.height(),
        color);
}





// extern
void drawBorder(int x, int y, int w, int h, int b, int color)
	// draw a frigin border
{
	tft.fillRect(x,		y,		b,		h,	color);
	tft.fillRect(x+w-b,	y,		b,		h,	color);
	tft.fillRect(x,		y,		w,		b,	color);
	tft.fillRect(x,		y+h-b,	w,		b,	color);
}


// extern
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
	...)
{
	va_list args;
	va_start(args, format);
	printfvJustified(x,y,w,h,just,fc,bc,use_bc,format,args);
}


// extern
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


// extern
void printJustified(
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
	int yoffset = 16;   // undefined: tft.getTextSizeY();   // getFontHeight();

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
			int pix = 16;   // undefined: tft.getTextSizeX();   // getCharWidth(c);

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





