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
#include <chips\pic-i8259.h>
#include <irq.h>
#include <swints.h>
#include <cpu\cpu.h>
#include <cpu\exceptions.h>

#define MAX_HANDLERS_PER_IRQ 8

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
struct IRQ_HANDLER
{
	int (*handler)(struct IRQ_DETAILS*);
	uint32_t flags;
	uint32_t owner;
};

struct IRQ_HANDLER hwd_irq_handlers[MAX_HARDWARE_INTERRUPTS][MAX_HANDLERS_PER_IRQ];

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
	struct IRQ_HANDLER *handlers = hwd_irq_handlers[state->intid - MAX_CPU_EXCEPTIONS];
	struct IRQ_DETAILS details = {state->intid - MAX_CPU_EXCEPTIONS};
	
    while((handlers->handler) != 0)
	{
       (*(handlers->handler))(&details);
	   handlers++;
	}
	pic_send_command_eoi(state->intid - MAX_CPU_EXCEPTIONS);
}

/*===============================================================================================*/
// Interface Functions
/*===============================================================================================*/
/*************************************************************************************************
	<summary>irq_install_handler</summary>
	<para>installs a hardware interrupt handler</para>
	<param name="IRQ_id" type="unsigned int">interrupt request id</param>
	<param name="handler" type="int (*handler)(struct IRQ_DETAILS*)">the address of the handler function</param>
	<param name="flags" type="uint32_t">interrupt flags</param>
	<returns>
		IRQ_UNUSED if the IRQ is not supported/used by the architecture.
		IRQ_HANDLERS_FULL if another handler cannot be added
	</returns>
*************************************************************************************************/
int irq_install_handler(int IRQ_id, int (*handler)(struct IRQ_DETAILS*), uint32_t flags)
{
	if(IRQ_id >= MAX_HARDWARE_INTERRUPTS) return IRQ_UNUSED;

	struct IRQ_HANDLER *handlers = hwd_irq_handlers[IRQ_id];
	for(int i = 0; i < MAX_HANDLERS_PER_IRQ; i++)
	{
		if(handlers[i].handler == 0)
		{
			handlers[i].handler = handler;
			return 0;
		}
	}
	return IRQ_HANDLERS_FULL;
}

/*************************************************************************************************
	<summary>irq_uninstall_handler</summary>
	<para>installs a hardware interrupt handler</para>
	<param name="IRQ_id" type="unsigned int">interrupt request id</param>
	<returns>
		IRQ_UNUSED if the IRQ is not supported/used by the architecture.
		IRQ_DEFAULT_HANDLER if a handler for the IRQ does not exist exists
	</returns>
*************************************************************************************************/
int irq_uninstall_handler(int IRQ_id)
{	
	/*if(IRQ_id >= MAX_HARDWARE_INTERRUPTS) return IRQ_UNUSED;
	
	struct IRQ_HANDLER *handlers = hwd_irq_handlers[state->intid - MAX_CPU_EXCEPTIONS];
	for(int i = 0; i < MAX_HANDLERS_PER_IRQ; i++)
	{
		 if(handlers[i].handler == handler)
		 {
			handlers[i].handler = handler;
			return 0;
		 }
	}*/
	return IRQ_HANDLERS_FULL;
}

/*************************************************************************************************
	<summary>irq_get_handler</summary>
	<para>gets a pointer to the handler function</para>
	<param name="IRQ_id" type="unsigned int">interrupt request id</param>
	<returns>
		IRQ_UNUSED if the IRQ is not supported/used by the architecture.
		IRQ_DEFAULT_HANDLER if a handler for the IRQ does not exist exists
		the address of the handler function if it exists, 0 if a handler does not exist
	</returns>
*************************************************************************************************/
void *irq_get_handler(int IRQ_id)
{	
	if(IRQ_id >= MAX_HARDWARE_INTERRUPTS) return (void *)IRQ_UNUSED;
	if(hwd_irq_handlers[IRQ_id] == 0) return (void *)IRQ_DEFAULT_HANDLER;	
	return hwd_irq_handlers[IRQ_id];
}

/*************************************************************************************************
	<summary>irq_enable</summary>
	<para>enables hardware interrupts</para>
*************************************************************************************************/
void irq_enable()
{
	__asm__ ("sti");
}

/*************************************************************************************************
	<summary>irq_disable</summary>
	<para>disables hardware interrupts</para>
*************************************************************************************************/
void irq_disable()
{
	__asm__ ("cli");
}