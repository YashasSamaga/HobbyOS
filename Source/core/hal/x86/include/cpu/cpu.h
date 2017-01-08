/************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Processor Interface
//
//	cpu.h
//	Provides an interface to work with the processor.
//
//	* private to HAL (cannot be accessed outside the HAL)
//
//	Date: January 6th 2017
//
/************************************************************************************************/
#ifndef _CPU_H
#define _CPU_H

#include<stdint.h>

/*==============================================================================================*/
// Interface Structures
/*==============================================================================================*/
struct cpu_regs
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t intid, errorcode;
    uint32_t eip, cs, eflags, useresp, ss;
};

/*==============================================================================================*/
// Interface Functions
/*==============================================================================================*/
extern int cpu_initialize ();
extern void cpu_shutdown ();

#endif // _CPU_H
