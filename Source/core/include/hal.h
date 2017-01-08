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
#include <lindus-specifics\ls-exceptions.h>

extern int exception_install_handler(unsigned int ls_exception_id, void (*handler)());
extern int exception_uninstall_handler(unsigned int ls_exception_id);
extern void *exception_get_handler(unsigned int ls_exception_id);

extern void irq_enable();
extern void irq_disable();

extern void clrscr ();
extern void puts (char* str);
extern int printf (const char* str, ...);
extern unsigned setattribute (enum color foreground, enum color background);
extern void gotoxy (unsigned x, unsigned y);

#endif // _HAL_H
