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
#include <pic.h>
#include <irq.h>
#include <swints.h>
#include <cpu\cpu.h>
#include <cpu\exceptions.h>

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
void *hwd_irq_handlers[MAX_HARDWARE_INTERRUPTS];

/*==============================================================================================*/
// Implementation Functions (Private)
/*==============================================================================================*/
/*************************************************************************************************
	<summary>hwd_irq_handler</summary>
	<para>called from the hardware interrupt handler in init.asm</para>
	<param name="state" type="struct cpu_regs">contents of the cpu registers</param>
*************************************************************************************************/
void hwd_irq_handler(struct cpu_regs *state)
{	
	void (*handler)() = hwd_irq_handlers[state->intid - MAX_CPU_EXCEPTIONS];
    if ((handler) != 0)
	{
       handler();
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
	<param name="handler" type="function pointer">the address of the handler function</param>
	<returns>
		IRQ_UNUSED if the IRQ is not supported/used by the architecture.
		IRQ_HANDLER_EXISTS if a handler for the IRQ already exists
	</returns>
*************************************************************************************************/
int irq_install_handler(unsigned int IRQ_id, void (*handler)())
{
	if(IRQ_id >= MAX_HARDWARE_INTERRUPTS || IRQ_id < 0) return IRQ_UNUSED;
	if(hwd_irq_handlers[IRQ_id] != 0) return IRQ_HANDLER_EXISTS;	
    hwd_irq_handlers[IRQ_id] = handler;
	return 0;
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
int irq_uninstall_handler(unsigned int IRQ_id)
{	
	if(IRQ_id >= MAX_HARDWARE_INTERRUPTS || IRQ_id < 0) return IRQ_UNUSED;
	if(hwd_irq_handlers[IRQ_id] == 0) return IRQ_DEFAULT_HANDLER;	
    hwd_irq_handlers[IRQ_id] = 0;
	return 0;
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
void *irq_get_handler(unsigned int IRQ_id)
{	
	if(IRQ_id >= MAX_HARDWARE_INTERRUPTS || IRQ_id < 0) return (void *)IRQ_UNUSED;
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