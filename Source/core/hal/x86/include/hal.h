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

#include <stdint.h>

/*===============================================================================================*/
// Interface Functions
/*===============================================================================================*/
/*************************************************************************************************
	<summary>inportb</summary>
	<para>inputs a byte from the specified port</para>
	<param name="port" type="uint16_t"></param>
	<returns type="uint8_t">byte received from the port</returns>
*************************************************************************************************/
inline uint8_t inportb(uint16_t _port)
{
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/*************************************************************************************************
	<summary>outportb</summary>
	<para>outputs a byte to the specified port</para>
	<param name="port" type="uint16_t"></param>
	<param name="data" type="uint8_t"></param>
*************************************************************************************************/
inline void outportb(uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/*************************************************************************************************
	<summary>io_wait</summary>
	<para>Waits for an IO operation to complete</para>
	<remarks>Required to fix buggy motherboards (486 and below)</remarks>
*************************************************************************************************/
inline void io_wait(void)
{
    __asm__ __volatile__ ( "outb %%al, $0x80" : : "a"(0) );
}

extern void clrscr ();
extern void puts (char* str);
extern int printf (const char* str, ...);
extern uint8_t setattribute (int foreground, int background);
extern void gotoxy (unsigned x, unsigned y);
#endif // _HAL_LOCAL_H
