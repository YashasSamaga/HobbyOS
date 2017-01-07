/************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//
//	The hardware abstraction layer provides an 'abstract' hardware independent interface to 
// 	control the hardware from the kernel. The hardware abstraction layer is the first component
// 	to be loaded by the bootloader. The hardware abstraction layer is responsible for initilizing
//  the basic devices and controllers after which control is transfered to the kernel.
//
//	hal.c
//	Hardware abstraction layer implementation code	
//
//	Date: January 6th 2017
//
/************************************************************************************************/
#include "hal.h"
#include "cpu\cpu.h"

#include <hal.h>
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

/*===============================================================================================*/
// Implementation Functions (Private)
/*===============================================================================================*/
int hal_shutdown();

/*************************************************************************************************
	<summary>hal_initialize</summary>
	<para>initilizes the hardware abstraction layer</para>
	<remarks> 
		* entry point of the kernel (called from start wrapper in init.asm)
		* calls the kernel after HAL initilization
	</remarks>
*************************************************************************************************/
void hal_initialize() 
{
	cpu_initialize();
	
	// HAL initilized, execute kernel_init()
	extern int kernel_init();
	if(kernel_init() == 1) hal_shutdown (); // something went wrong, shutdown the computer
	
	for(;;);
}

/*************************************************************************************************
	<summary>hal_shutdown</summary>
	<para>carries out the shutdown processes</para>
*************************************************************************************************/
int hal_shutdown() 
{
	cpu_shutdown();
	return 0;
}
