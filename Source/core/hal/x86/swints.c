/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Interrupt Mangement
//
//	interrupts.c
//	Interface to work with interrupts.
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#include <stdint.h>

#include <hal.h>
#include <irq.h>
#include <swints.h>
#include <cpu\cpu.h>
#include <cpu\exceptions.h>

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
void *swint_handlers[MAX_SOFTWARE_INTERRUPTS];

/*==============================================================================================*/
// Implementation Functions (Private)
/*==============================================================================================*/
/*************************************************************************************************
	<summary>isr_default_handler</summary>
	<para>handles software interrupts and calls the correct registered handler</para>
	<param name="state" type="struct cpu_regs">contents of the cpu registers</param>
*************************************************************************************************/
void isr_default_handler(struct cpu_regs *state)
{	
	void (*handler)() = swint_handlers[state->intid - MAX_CPU_EXCEPTIONS - MAX_HARDWARE_INTERRUPTS];
    if ((handler) != 0)
	{
       handler();
	}
}

/*===============================================================================================*/
// Interface Functions
/*===============================================================================================*/
/*************************************************************************************************
	<summary>swint_install_handler</summary>
	<para>installs a software interrupt handler</para>
	<param name="swintid" type="unsigned int">software interrupt id</param>
	<param name="handler" type="function pointer">the address of the handler function</param>
	<returns>
		SWINT_UNUSED if the software interrupt is not supported/used by the architecture.
		SWINT_HANDLER_EXISTS if a handler for the IRQ already exists
	</returns>
*************************************************************************************************/
int swint_install_handler(unsigned int swintid, void (*handler)())
{
	if(swintid >= MAX_SOFTWARE_INTERRUPTS) return SWINT_UNUSED;
	if(swint_handlers[swintid] != 0) return SWINT_HANDLER_EXISTS;	
    swint_handlers[swintid] = handler;
	return 0;
}

/*************************************************************************************************
	<summary>swint_uninstall_handler</summary>
	<para>installs a hardware interrupt handler</para>
	<param name="swintid" type="unsigned int">software interrupt id</param>
	<returns>
		SWINT_UNUSED if the IRQ is not supported/used by the architecture.
		SWINT_DEFAULT_HANDLER if a handler for the IRQ does not exist exists
	</returns>
*************************************************************************************************/
int swint_uninstall_handler(unsigned int swintid)
{	
	if(swintid >= MAX_SOFTWARE_INTERRUPTS) return SWINT_UNUSED;
	if(swint_handlers[swintid] == 0) return SWINT_DEFAULT_HANDLER;	
    swint_handlers[swintid] = 0;
	return 0;
}

/*************************************************************************************************
	<summary>swint_get_handler</summary>
	<para>gets a pointer to the handler function</para>
	<param name="swintid" type="unsigned int">software interrupt id</param>
	<returns>
		SWINT_UNUSED if the IRQ is not supported/used by the architecture.
		SWINT_DEFAULT_HANDLER if a handler for the IRQ does not exist exists
		the address of the handler function if it exists, 0 if a handler does not exist
	</returns>
*************************************************************************************************/
void *swint_get_handler(unsigned int swintid)
{	
	if(swintid >= MAX_SOFTWARE_INTERRUPTS) return (void *)SWINT_UNUSED;
	if(swint_handlers[swintid] == 0) return (void *)SWINT_DEFAULT_HANDLER;	
	return swint_handlers[swintid];
}