/************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Basic textmode display functions (tty)
//
//	textmode.c
//	This file contains 'bad' implementations of display functions for basic text output terminal 	
//
//	Date: January 6th 2017
//
/************************************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#include <hal.h>

/*==============================================================================================*/
// Defines and Enumerations (Private)
/*==============================================================================================*/
#define VIDEO_MEMORY_COLOR 	0xB8000
#define VIDEO_MEMORY_MONO 	0xB0000

#define TEXTMODE_MAX_X 80
#define TEXTMODE_MAX_Y 25

typedef enum textmode_types
{
	TEXTMODE_INVALID = 0x70, // not standard
	TEXTMODE_UNKNOWN = 0x60, // not standard
    TEXTMODE_NONE = 0x00,
    TEXTMODE_COLOUR = 0x20,
    TEXTMODE_MONOCHROME = 0x30,
}textmode_types;

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
static uint16_t *vmemptr;

static uint8_t curPos_x = 0, curPos_y = 0;
static uint8_t startX = 0, startY = 0;

static uint8_t attribute = 0x0F;
static textmode_types textmode_type = TEXTMODE_INVALID;

/*==============================================================================================*/
// Implementation Functions (Private)
/*==============================================================================================*/
/*************************************************************************************************
	<summary>init_textmode</summary>
	<para>identifies the display mode/device and sets the video memory pointer appropriately</para>
*************************************************************************************************/
static void init_textmode()
{
    textmode_type = (*(volatile uint16_t*)0x410) & 0x30; // BIOS Data Area
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
 
/*************************************************************************************************
	<summary>updatecursor</summary>
	<para>communicates with the display hardware and sets the blinking cursor position</para>
*************************************************************************************************/
static void updatecursor()
{
	unsigned int temp = curPos_y * TEXTMODE_MAX_X + curPos_x;

    outportb(0x3D4, 0xE);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 0xF);
    outportb(0x3D5, temp);
}

/*************************************************************************************************
	<summary>putc</summary>
	<para>prints a character on the screen</para>
	<param name="c" type="unsigned char">the character that has to be printed</param>
	<remarks>updates the cursor automatically</remarks>
*************************************************************************************************/
static void putc(unsigned char c) 
{	
	switch(c)
	{
		case '\0': return;
		case '\b':
			if(curPos_x != 0) curPos_x--;
		break;
		
		case ' ':
			curPos_x++;
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

/*==============================================================================================*/
// Interface Functions
/*==============================================================================================*/
/*************************************************************************************************
	<summary>clrscr</summary>
	<para>clears the screen</para>
*************************************************************************************************/
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

/*************************************************************************************************
	<summary>setattribute</summary>
	<para>sets the character attribute byte</para>
	<returns>old character attribute byte</returns>
*************************************************************************************************/
uint8_t setattribute (int foreground, int background) 
{
	uint8_t old = attribute;
	attribute = foreground | (background << 4);
	return old;
}

/*************************************************************************************************
	<summary>gotoxy</summary>
	<para>moves the cursor to the given position</para>
	<param name="x" type="unsigned int">cursor's x position</param>
	<param name="y" type="unsigned int">cursor's y position</param>
*************************************************************************************************/
void gotoxy (unsigned int x, unsigned int y) 
{
	if(textmode_type == TEXTMODE_INVALID) init_textmode();
	if(textmode_type != TEXTMODE_COLOUR && textmode_type != TEXTMODE_MONOCHROME) return;
	
	curPos_x = x;
	curPos_y = y;
	startX = curPos_x;
	startY = curPos_y;
	updatecursor();
}

/*************************************************************************************************
	<summary>puts</summary>
	<para>prints a string on the screen</para>
	<param name="str" type="char *">string that has to be printed</param>
*************************************************************************************************/
void puts (char *str) 
{
	if(textmode_type == TEXTMODE_INVALID) init_textmode();
	if(textmode_type != TEXTMODE_COLOUR && textmode_type != TEXTMODE_MONOCHROME) return;

	if (!str)
		return;

	for (size_t i = 0, len = strlen (str); i < len; i++)
		putc(str[i]);
}

/*************************************************************************************************
	<summary>printf</summary>
	<para>prints a formatted string</para>
	<param name="str" type="const char *">command id</param>
	<param name="..."></param>
	<returns>
		0 on success
		1 on failure
	</returns>
	<remarks>
		Specifiers:
		%% - prints a %
		%c - prints a character
		%s - prints a string
		%d - prints an integer
		%i - prints an integer
		%x - prints a hexadecimal number
		%p - prints an address
		%o - prints an octal number
		
		In case an error is encountered, whatever was supposed to be printed before the error character will be printed.
	</remarks>
*************************************************************************************************/
int printf (const char *str, ...) 
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
					// print a %
					case '%':
					{
						putc ('%');
						break;
					}
					// character
					case 'c': 
					{
						char c = va_arg (args, char);
						putc (c);
						break;
					}					
					// string
					case 's': 
					{
						char * tmp = va_arg (args, char *);
						puts (tmp);
						break;
					}
					// integers
					case 'd':
					case 'i': 
					{
						int c = va_arg (args, int);
						char tmp[32] = "\0";
						itoa_s (c, 10, tmp);
						puts (tmp);
						break;
					}
					// hexadecimal numbers and pointer addresses
					case 'b':
					{
						int c = va_arg (args, int);
						char tmp[33] = "\0";
						itoa(c, 2, tmp);
						puts (tmp);
						break;
					}
					case 'x':
					case 'p':
					{
						int c = va_arg (args, int);
						putc('0');
						putc('x');
						char tmp[32] = "\0";
						itoa(c,16,tmp);
						puts (tmp);
						break;
					}
					// octal numbers
					case 'o': 
					{
						int c = va_arg (args, int);
						putc('0');
						char tmp[32] = "\0";
						itoa_s (c,8,tmp);
						puts (tmp);
						break;
					}
					default:
						va_end (args);
						return 0;
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
