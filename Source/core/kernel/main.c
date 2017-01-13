/******************************************************************************/
//	Kernel
//
//	main.c
//	Date: January 6th 2017
//
/******************************************************************************/
#define ARCH_X86

#include "hal.h"

int kernel_init() //called from the hardware abstraction layer
{
	setattribute(1, 3);
	clrscr();	
	printf("Hi");
	for(;;);
}