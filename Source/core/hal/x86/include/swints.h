/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Interrupt Mangement
//
//	interrupts.h
//	Interface to work with interrupts.
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#ifndef _INTERRUPT_H
#define _INTERRUPT_H

/*==============================================================================================*/
// Defines and Enumerations
/*==============================================================================================*/
#define MAX_SOFTWARE_INTERRUPTS 224

enum 
{
	SWINT_HANDLER_EXISTS = 1,
	SWINT_UNUSED,
	SWINT_DEFAULT_HANDLER	
};

int swint_install_handler(unsigned int swintid, void (*handler)());
int swint_uninstall_handler(unsigned int swintid);
void *swint_get_handler(unsigned int swintid);

#endif // _INTERRUPT_H
