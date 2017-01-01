/********************************************************************/
//Lindus Text Mode Screen Driver
//Date: 21-4-2012
//Author: Yashas Samaga
//Description: Basic Screen IO for Text Mode
//
//Copyright (C) Yashas Samaga
/********************************************************************/
#ifndef _SCREEN_H
	#define _SCREEN_H

	extern int get_x();
	extern int get_y();
	extern int get_attribute();
	extern unsigned short get_currentmem();
	extern void update_cursor(int row_y, int col_x);
	extern unsigned short get_exactmem();
	extern void printf(unsigned char *text);
	extern void scroll();
	extern void clearscr();
	extern void print(char chr);


#endif
