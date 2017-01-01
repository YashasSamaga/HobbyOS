/********************************************************************************/
//Text Mode Screen Driver
//Author  :   Yashas Samaga
//Date    :   21-04-2012
//Description: This has the routins for printing,cursor,scrolling,etc for text 
//             mode.
//
//Copyright (C) Yashas Samaga <yashas_2010@yahoo.com>
/********************************************************************************/
#include <system.h>
#include <lib\string.h>
#include <drivers\tm\screen.h>
#include <init.h>
//////////////////////////////////////////////////////////////////////////////////
#define TEXTMEM 0xB8000
//////////////////////////////////////////////////////////////////////////////////
unsigned short *textmem;
int attribute = 0x07;
static int cursorx = 0, cursory = 0;
//////////////////////////////////////////////////////////////////////////////////
int get_x(){return cursorx;}
int get_y(){return cursory;}
int get_attribute(){return attribute;}
unsigned short get_currentmem(){return textmem;}
unsigned short get_exactmem(){return textmem + (cursory*80 + cursorx);}
//////////////////////////////////////////////////////////////////////////////////
void update_cursor(int row_y, int col_x)
{
	unsigned short position=(row_y*80) + col_x;
	cursorx = col_x;
	cursory = row_y;
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (unsigned char)(position&0xFF));
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (unsigned char )((position>>8)&0xFF));
}
void scroll()
{
	unsigned blank, temp;
	blank = 0x20 | (attribute << 8);
	if(cursory >= 25)
	{
		temp = cursory - 25 + 1;
		memcpy (textmem, textmem + temp * 80, (25 - temp) * 80 * 2);
		memsetw (textmem + (25 - temp) * 80, blank, 80);
		cursory = 25 - 1;
	}
}
void clearscr()
{
	unsigned short blank = 0x20 | (attribute << 8);
	int i;

	for (i = 0; i < 80*25; i++)
	{
		textmem[i] = blank;
	}
	update_cursor(0,0);
}
void print(char chr)
{
	unsigned short *location;
	int numtab = 8;
	if (chr == 0x08 && cursorx)
	{
		cursorx--;
	}
	else if (chr == 0x09)
	{
		cursorx = (cursorx+ numtab) & ~( numtab -1);
	}
	else if (chr == '\r')
	{
		cursorx = 0;
	}
	else if (chr == '\n')
	{
		cursorx = 0;
		cursory++;
	}
	else if(chr >=' ')
	{
		location = textmem + (cursory*80 + cursorx);            
		*location = chr | (attribute << 8);
		cursorx++;
	}
	if (cursorx>= 80)
	{
		cursorx = 0;
		cursory++;
	}
	scroll();
	update_cursor(cursory,cursorx);
}
void printf(unsigned char *text)
{
	int i;
	for (i = 0; i < strlen(text); i++)
	{
		print(text[i]);
	}
}
void set_color(unsigned char forecolor, unsigned char backcolor)
{
    attribute = (backcolor << 4) | (forecolor & 0x0F);
}
void init_console()
{
	textmem = (unsigned short *) 0xB8000;
	clearscr();
} 
