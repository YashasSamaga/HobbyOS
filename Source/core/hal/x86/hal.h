/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//
//	The hardware abstraction layer provides an 'abstract' hardware independent interface to 
// 	control the hardware from the kernel. The hardware abstraction layer is the first component
// 	to be loaded by the bootloader. The hardware abstraction layer is responsible for initilizing
//  the basic devices and controllers after which control is transfered to the kernel.
//
//	hal.h (local)
//
//	Implementation Header (private)
//	* accessible by HAL code only
//
//	Date: January 6th 2017
//
/*************************************************************************************************/
#ifndef _HAL_LOCAL_H
#define _HAL_LOCAL_H

#define ARCH_X86

#include <stdint.h>

/*===============================================================================================*/
// Interface Function Prototypes
/*===============================================================================================*/
extern uint8_t inportb (uint16_t _port);
extern void outportb (uint16_t _port, uint8_t _data);

#endif // _HAL_LOCAL_H
