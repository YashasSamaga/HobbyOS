/******************************************************************************/
//	Kernel
//
//	main.c
//	Date: January 6th 2017
//
/******************************************************************************/
#define ARCH_X86

#include "hal.h"

int kernel_init()
{
	setattribute(15, 3);
	printf("\n\nHi from Kernel");
	for(;;);
}