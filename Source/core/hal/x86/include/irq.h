/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Hardware Interrupt Mangement
//
//	irq.h
//	Interface to work with hardware interrupts.
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#ifndef _IRQ_H
#define _IRQ_H

/*==============================================================================================*/
// Defines and Enumerations
/*==============================================================================================*/
#define MAX_HARDWARE_INTERRUPTS 16

struct IRQ_DETAILS
{
	int irq_number;
};

enum 
{	
	IRQ_UNUSED = -1,
	IRQ_HANDLER_EXISTS = -2,
	IRQ_DEFAULT_HANDLER = -3,
	IRQ_HANDLERS_FULL = -4
};

/*==============================================================================================*/
// Interface Function Prototypes
/*==============================================================================================*/
extern int irq_install_handler(unsigned int IRQ_id, int (*handler)(struct IRQ_DETAILS*), uint32_t flags);
extern int irq_uninstall_handler(unsigned int IRQ_id);
extern void* irq_get_handler(unsigned int irq_handler_id);

/*************************************************************************************************
	<summary>irq_enable</summary>
	<para>enables hardware interrupts</para>
*************************************************************************************************/
#define irq_enable() __asm__ ("sti")

/*************************************************************************************************
	<summary>irq_disable</summary>
	<para>disables hardware interrupts</para>
*************************************************************************************************/
#define irq_disable() __asm__ ("cli")

#endif // _IRQ_H
