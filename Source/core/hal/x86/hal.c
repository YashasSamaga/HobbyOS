/******************************************************************************/
//	Hardware Abstraction Layer x86
//
//	HAL Entry Function
//
//	hal.c
//	Date: January 6th 2017
//
/******************************************************************************/

#include "hal.h"
#include "cpu.h"
#include <hal.h>

int hal_shutdown () 
{
	cpu_shutdown();
	return 0;
}
int hal_initialize () 
{
	setattribute(COLOR_BLACK, COLOR_CYAN);
	clrscr();
	printf("HAL initilization\n");
	cpu_initialize();
	
	// HAL initilized, execute kernel_init()
	extern int kernel_init();
	if(kernel_init() == 1) hal_shutdown (); // something went wrong, shutdown the computer
	
	for(;;);
	return 0;
}

/*void _cdecl geninterrupt (int n) {
#ifdef _MSC_VER
	_asm {
		mov al, byte ptr [n]
		mov byte ptr [genint+1], al
		jmp genint
	genint:
		int 0	// above code modifies the 0 to int number to generate
	}
#endif
}*/