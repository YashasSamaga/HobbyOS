/******************************************************************************/
//	Generic Hardware Abstraction Layer (HAL)
//
//	Implementations required by the kernel which are hardware specific
// 	HAL is hardware dependent (architecture dependent)
//	This header provides an interface to access the HAL from the kernel
//
//	hal.h (global)
//	Date: January 6th 2017
//
/******************************************************************************/
#ifndef _HAL_H
#define _HAL_H

#ifndef ARCH_X86
	#error "Unknown Architecture"
#endif

#include <stdint.h>

enum color
{ 	
	COLOR_BLACK = 0, 	
	COLOR_BLUE = 1, 	
	COLOR_GREEN = 2, 	
	COLOR_CYAN = 3, 	
	COLOR_RED = 4, 	
	COLOR_MAGENTA = 5, 	
	COLOR_BROWN = 6, 	
	COLOR_LIGHT_GREY = 7, 	
	COLOR_DARK_GREY = 8, 	
	COLOR_LIGHT_BLUE = 9, 	
	COLOR_LIGHT_GREEN = 10, 	
	COLOR_LIGHT_CYAN = 11, 	
	COLOR_LIGHT_RED = 12, 	
	COLOR_LIGHT_MAGENTA = 13, 	
	COLOR_LIGHT_BROWN = 14, 	
	COLOR_WHITE = 15 
};

extern void clrscr ();
extern void puts (char* str);
extern int printf (const char* str, ...);
extern unsigned setattribute (enum color foreground, enum color background);
extern void gotoxy (unsigned x, unsigned y);

#endif // _HAL_H
