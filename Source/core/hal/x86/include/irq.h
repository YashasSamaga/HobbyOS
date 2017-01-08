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

enum 
{
	IRQ_HANDLER_EXISTS = 1,
	IRQ_UNUSED,
	IRQ_DEFAULT_HANDLER	
};

/*==============================================================================================*/
// Interface Function Prototypes
/*==============================================================================================*/
extern int irq_install_handler(unsigned int IRQ_id, void (*handler)());
extern int irq_uninstall_handler(unsigned int IRQ_id);
extern void *irq_get_handler(unsigned int IRQ_id);
extern void irq_enable();
extern void irq_disable();

#endif // _IRQ_H
