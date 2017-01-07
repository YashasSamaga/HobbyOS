/******************************************************************************/
//	Basic Text Mode Display Routines (TTY)
//	Hardware Abstraction Layer x86
//
//	textmode.c
//	Date: January 5th 2017
//
/******************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "hal.h"
#include <hal.h>

#define VIDEO_MEMORY_COLOR 	0xB8000
#define VIDEO_MEMORY_MONO 	0xB0000

#define TEXTMODE_MAX_X 80
#define TEXTMODE_MAX_Y 25

typedef enum textmode_types
{
	TEXTMODE_INVALID = 0x70,
	TEXTMODE_UNKNOWN = 0x60,
    TEXTMODE_NONE = 0x00,
    TEXTMODE_COLOUR = 0x20,
    TEXTMODE_MONOCHROME = 0x30,
}textmode_types;

static uint16_t *vmemptr;

static uint8_t curPos_x = 0, curPos_y = 0;
static uint8_t startX = 0, startY = 0;

static uint8_t attribute = 0x0F;
static textmode_types textmode_type = TEXTMODE_INVALID;


void init_textmode()
{
    textmode_type = (*(volatile uint16_t*)0x410) & 0x30;
    switch(textmode_type)
    {
		case TEXTMODE_COLOUR: 
			vmemptr = (uint16_t*)VIDEO_MEMORY_COLOR;			
		break;
		case TEXTMODE_MONOCHROME:
			vmemptr = (uint16_t*)VIDEO_MEMORY_MONO;
		break;
		case TEXTMODE_NONE:
		break;
		default:
			textmode_type = TEXTMODE_UNKNOWN;
		break;
    }
 }
 
/* private functions do not need the textmode initilization and type checks */
/* the functions calling these private functions will be having their own checks */
/* 	
	if(textmode_type == TEXTMODE_INVALID) init_textmode();
	if(textmode_type != TEXTMODE_COLOUR && textmode_type != TEXTMODE_MONOCHROME) return; 
*/
void updatecursor()
{
	unsigned int temp = curPos_y * TEXTMODE_MAX_X + curPos_x;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void putc(unsigned char c) 
{	
	switch(c)
	{
		case '\0': return;
		case '\b':
			if(curPos_x != 0) curPos_x--;
		break;
		
		case '\t':
			curPos_x = (curPos_x + 8) & ~(8 - 1);
		break;
		
		case '\r':
			curPos_x = 0;
		break;
		
		case '\n':
			curPos_x = 0;
			curPos_y++;
		break;
		
		default:
		{
			if(isprint(c))
			{
				uint16_t *where = vmemptr + (curPos_y * TEXTMODE_MAX_X + curPos_x);
				*where = c | (attribute << 8);
				curPos_x++;
			}
			break;
		}
	}	
	if(curPos_x >= TEXTMODE_MAX_X)
    {
        curPos_x = 0;
        curPos_y++;
    }	
    if(curPos_y >= TEXTMODE_MAX_Y)
    {
		uint16_t blank = 0x20 | (attribute << 8);
        unsigned int temp = curPos_y - TEXTMODE_MAX_Y + 1;
        memcpy (vmemptr, vmemptr + temp * TEXTMODE_MAX_X, (TEXTMODE_MAX_Y - temp) * TEXTMODE_MAX_X * 2);
        memsetw (vmemptr + (TEXTMODE_MAX_Y - temp) * TEXTMODE_MAX_X, blank, TEXTMODE_MAX_X);
        curPos_y = TEXTMODE_MAX_Y - 1;
    }
	updatecursor();
}

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void itoa(unsigned i, unsigned base, char *buf) 
{
   int pos = 0;
   int opos = 0;
   int top = 0;

   if (i == 0 || base > 16) 
   {
      buf[0] = '0';
      buf[1] = '\0';
      return;
   }

   while (i != 0) 
   {
      tbuf[pos] = bchars[i % base];
      pos++;
      i /= base;
   }
   top=pos--;
   for (opos=0; opos<top; pos--,opos++) 
   {
      buf[opos] = tbuf[pos];
   }
   buf[opos] = 0;
}

void itoa_s(int i, unsigned base, char *buf) 
{
   if (base > 16) return;
   if (i < 0) 
   {
      *buf++ = '-';
      i *= -1;
   }
   itoa(i,base,buf);
}

unsigned setattribute (enum color foreground, enum color background) 
{
	unsigned old = attribute;
	attribute = foreground | (background << 4);
	return old;
}

void gotoxy (unsigned x, unsigned y) 
{
	if(textmode_type == TEXTMODE_INVALID) init_textmode();
	if(textmode_type != TEXTMODE_COLOUR && textmode_type != TEXTMODE_MONOCHROME) return;
	
	curPos_x = x;
	curPos_y = y;
	startX = curPos_x;
	startY = curPos_y;
	updatecursor();
}

void clrscr () 
{
	if(textmode_type == TEXTMODE_INVALID) init_textmode();
	if(textmode_type != TEXTMODE_COLOUR && textmode_type != TEXTMODE_MONOCHROME) return;
	
	uint16_t blank = 0x20 | (attribute << 8);

    for(int i = 0; i < TEXTMODE_MAX_Y; i++)
		for(int j = 0; j < TEXTMODE_MAX_X; j++)
			*(vmemptr + i*TEXTMODE_MAX_X + j) = blank;
	
    curPos_x = 0;
    curPos_y = 0;
	updatecursor();
	return;
}

void puts (char* str) 
{
	if(textmode_type == TEXTMODE_INVALID) init_textmode();
	if(textmode_type != TEXTMODE_COLOUR && textmode_type != TEXTMODE_MONOCHROME) return;

	if (!str)
		return;

	for (size_t i = 0, len = strlen (str); i < len; i++)
		putc(str[i]);
}

int printf (const char* str, ...) 
{
	if(textmode_type == TEXTMODE_INVALID) init_textmode();
	if(textmode_type != TEXTMODE_COLOUR && textmode_type != TEXTMODE_MONOCHROME) return 0;
	
	if(!str)
		return 0;

	va_list	args;
	va_start (args, str);

	for (size_t i = 0, len = strlen(str); i < len; i++) 
	{
		switch (str[i])
		{
			case '%':
			{
				switch (str[++i]) 
				{
					case '%':
					{
						putc ('%');
						break;
					}
					
					/* characters */					
					case 'c': 
					{
						char c = va_arg (args, char);
						putc (c);
						break;
					}

					/* address of */
					case 's': 
					{
						char * tmp = va_arg (args, char *);
						puts (tmp);
						break;
					}

					/* integers */
					case 'd':
					case 'i': 
					{
						int c = va_arg (args, int);
						char tmp[32] = "\0";
						itoa_s (c, 10, tmp);
						puts (tmp);
						break;
					}

					/* display in hex */
					case 'X':
					case 'x': 
					{
						int c = va_arg (args, int);
						putc('0');
						putc('x');
						char tmp[32] = "\0";
						itoa_s (c,16,tmp);
						puts (tmp);
						break;
					}

					default:
						va_end (args);
						return 1;
				}
				break;
			}
			default:
				putc (str[i]);
				break;
		}
	}
	va_end (args);
	return 1;
}
