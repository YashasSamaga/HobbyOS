/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Hardware Interrupt Mangement
//
//	irq.c
//	Interface to work with hardware interrupts.
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#include <stdint.h>

#include <hal.h>
#include <chips/pic-i8259.h>
#include <irq.h>
#include <swints.h>
#include <cpu/cpu.h>
#include <cpu/exceptions.h>

/*==============================================================================================*/
// Implementation Defines (Private)
/*==============================================================================================*/
#define MAX_HANDLERS_PER_IRQ 8

/*==============================================================================================*/
// Implementation Structures (Private)
/*==============================================================================================*/
struct IRQ_HANDLER
{
	int (*handler_function)(struct IRQ_DETAILS*);
	uint32_t flags;
};

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
static struct IRQ_HANDLER irq_handler_list[MAX_HARDWARE_INTERRUPTS][MAX_HANDLERS_PER_IRQ];

/*===============================================================================================*/
// Implementation Functions (Private)
/*===============================================================================================*/
/*************************************************************************************************
	<summary>hwd_irq_handler</summary>
	<para>called from the hardware interrupt handler in init.asm</para>
	<param name="state" type="struct cpu_regs">contents of the cpu registers</param>
*************************************************************************************************/
void hwd_irq_handler(struct cpu_regs *state)
{	
	// in x86 architecture, the first 32 interrupts are reserved for CPU exceptions
	// we use the next 16 interrupts for IRQs
	int current_irq = state->intid - MAX_CPU_EXCEPTIONS;
	
	struct IRQ_DETAILS details;
	details.irq_number = current_irq;	

	for(int i = 0; i < MAX_HANDLERS_PER_IRQ; i++)
	{
		if((irq_handler_list[current_irq][i].handler_function) != 0)
		{
		   if((*(irq_handler_list[current_irq][i].handler_function))(&details))
		   {
				//IRQ was handled
		   }
		}
	}
	pic_send_command_eoi(current_irq);
}

/*===============================================================================================*/
// Interface Functions
/*===============================================================================================*/
/*************************************************************************************************
	<summary>irq_install_handler</summary>
	<para>installs a hardware interrupt handler</para>
	<param name="irq_no" type="unsigned int">interrupt request id</param>
	<param name="handler" type="int (*handler)(struct IRQ_DETAILS*)">the address of the handler function</param>
	<param name="flags" type="uint32_t">interrupt flags</param>
	<returns>
		IRQ_UNUSED if the IRQ is not supported/used by the architecture.
		IRQ_HANDLERS_FULL if another handler cannot be added
		The unique id assigned to the handler.
	</returns>
*************************************************************************************************/
int irq_install_handler(unsigned int irq_no, int (*handler)(struct IRQ_DETAILS*), uint32_t flags)
{
	if(irq_no >= MAX_HARDWARE_INTERRUPTS) return IRQ_UNUSED;

	for(int i = 0; i < MAX_HANDLERS_PER_IRQ; i++)
	{
		if(irq_handler_list[irq_no][i].handler_function == 0)
		{
			irq_handler_list[irq_no][i].handler_function = handler;
			irq_handler_list[irq_no][i].flags = flags;
			
			// position of the handler in the irq_handler_list is used as the handler's id
			// return the unique id number so that the same can be used to unregister the handler
			return (irq_no*MAX_HANDLERS_PER_IRQ + i);
		}
	}
	return IRQ_HANDLERS_FULL;
}

/*************************************************************************************************
	<summary>irq_uninstall_handler</summary>
	<para>installs a hardware interrupt handler</para>
	<param name="irq_handler_id" type="unsigned int">IRQ handler id (assigned by irq_install_handler)</param>
	<returns>
		IRQ_UNUSED if the IRQ is not supported/used by the architecture.
		IRQ_DEFAULT_HANDLER if a handler for the IRQ does not exist exists
	</returns>
*************************************************************************************************/
int irq_uninstall_handler(unsigned int irq_handler_id)
{	
	if(irq_handler_id >= MAX_HARDWARE_INTERRUPTS*MAX_HANDLERS_PER_IRQ) return IRQ_UNUSED;
	
	unsigned int irq_no = irq_handler_id/MAX_HANDLERS_PER_IRQ,
		idx = irq_handler_id%MAX_HANDLERS_PER_IRQ;
	
	if(irq_handler_list[irq_no][idx].handler_function != 0)
	{
		irq_handler_list[irq_no][idx].handler_function = 0;
		return 0;
	}
	return IRQ_DEFAULT_HANDLER;
}

/*************************************************************************************************
	<summary>irq_get_handler</summary>
	<para>gets a pointer to the handler function</para>
	<param name="irq_handler_id" type="unsigned int">IRQ handler id (assigned by irq_install_handler)</param>
	<returns>
		IRQ_UNUSED if the IRQ is not supported/used by the architecture.
		IRQ_DEFAULT_HANDLER if a handler for the IRQ does not exist exists
		the address of the handler function if it exists, 0 if a handler does not exist
	</returns>
*************************************************************************************************/
void* irq_get_handler(unsigned int irq_handler_id)
{	
	if(irq_handler_id >= MAX_HARDWARE_INTERRUPTS * MAX_HANDLERS_PER_IRQ) return (void*)IRQ_UNUSED;
	
	unsigned int irq_no = irq_handler_id/MAX_HANDLERS_PER_IRQ,
		idx = irq_handler_id%MAX_HANDLERS_PER_IRQ;
	
	if(irq_handler_list[irq_no][idx].handler_function == 0) return (void*)IRQ_DEFAULT_HANDLER;	
	return irq_handler_list[irq_no][idx].handler_function;
}