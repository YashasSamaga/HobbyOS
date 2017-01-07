/******************************************************************************/
//	Hardware Abstraction Layer (HAL)
//
//	Header for HAL specific code
//
//	hal.h (local)
//	Date: January 6th 2017
//
/******************************************************************************/
#ifndef _HAL_LOCAL_H
#define _HAL_LOCAL_H

#define ARCH_X86
/*============================================================================*/
//    IMPLEMENTATION FUNCTION PROTOTYPES
/*============================================================================*/

extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

#endif // _HAL_LOCAL_H
