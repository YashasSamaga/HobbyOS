/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	CPU Exception Mangement
//
//	exceptions.c
//	Interface to work with CPU Exception handlers.
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#include <stdint.h>

#include <lindus-specifics\ls-exceptions.h>

#include <hal.h>
#include <cpu\cpu.h>
#include <cpu\exceptions.h>

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
static const unsigned int i86_Exceptions[MAX_CPU_EXCEPTIONS] =
{
	LS_EXCEPT_DIV_BY_ZERO,
	LS_EXCEPT_DEBUG,			
	LS_EXCEPT_NMI,
	LS_EXCEPT_BREAKPOINT,
	LS_EXCEPT_OVERFLOW,
	LS_EXCEPT_BOUNDRANGE_EXCEEDED,
	LS_EXCEPT_INVALID_OPCODE,
	LS_EXCEPT_DEVICE_NOT_AVAIL,
	LS_EXCEPT_DOUBLE_FAULT,
	LS_EXCEPT_COPROC_SEG_OVERRUN,
	LS_EXCEPT_TASK_STATE_SEG,
	LS_EXCEPT_SEG_NOT_PRESENT,
	LS_EXCEPT_STACK_SEG_FAULT,
	LS_EXCEPT_GEN_PROTECTION_FAULT,
	LS_EXCEPT_PAGE_FAULT,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_X87_FPU,
	LS_EXCEPT_ALIGNMENT_CHECK,
	LS_EXCEPT_MACHINE_CHECK,
	LS_EXCEPT_SIMD_FPU,
	LS_EXCEPT_VIRTUALIZATION,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_RESERVED,
	LS_EXCEPT_TRIPLE_FAULT,
	LS_EXCEPT_FPU_ERROR_INT,
};

void *exception_handlers[MAX_CPU_EXCEPTIONS];
/*==============================================================================================*/
// Implementation Exception Handler (Private)
/*==============================================================================================*/
/*************************************************************************************************
	<summary>exception_handler</summary>
	<para>called from init.asm when an exception occures</para>
	<param name="state" type="struct cpu_regs">contents of the cpu registers</param>
*************************************************************************************************/
void exception_handler(struct cpu_regs *state)
{
    void (*handler)() = exception_handlers[state->intid];
    if ((handler) != 0)
	{
       handler();
	}
}

/*===============================================================================================*/
// Interface Functions
/*===============================================================================================*/
/*************************************************************************************************
	<summary>exception_install_handler</summary>
	<para>installs an exception handler</para>
	<param name="ls_exception_id" type="unsigned int">exception id according to lindus-specifications/exceptions</param>
	<param name="handler" type="function pointer">the address of the handler function</param>
	<returns>
		EXCEPTION_UNUSED if the LS Exception is not supported/used by the architecture.
		EXCEPTION_RESERVED if the LS Exception is reserved by the architecture
		EXCEPTION_HANDLER_EXISTS if a handler for the exception already exists
	</returns>
*************************************************************************************************/
int exception_install_handler(unsigned int ls_exception_id, void (*handler)())
{
	unsigned int CPU_ExceptionID = 0;
	for(; CPU_ExceptionID < MAX_CPU_EXCEPTIONS; CPU_ExceptionID++)
		if(i86_Exceptions[CPU_ExceptionID] == ls_exception_id) break;
	
	if(CPU_ExceptionID == MAX_CPU_EXCEPTIONS) return EXCEPTION_UNUSED;
	if(i86_Exceptions[CPU_ExceptionID] == LS_EXCEPT_RESERVED) return EXCEPTION_RESERVED;
	if(exception_handlers[CPU_ExceptionID] != 0) return EXCEPTION_HANDLER_EXISTS;
	
    exception_handlers[CPU_ExceptionID] = handler;
	return 0;
}

/*************************************************************************************************
	<summary>exception_uninstall_handler</summary>
	<para>uninstalls an exception handler</para>
	<param name="ls_exception_id" type="unsigned int">exception id according to lindus-specifications/exceptions</param>
	<returns>
		EXCEPTION_UNUSED if the LS Exception is not supported/used by the architecture.
		EXCEPTION_RESERVED if the LS Exception is reserved by the architecture
		EXCEPTION_DEFAULT_HANDLER if a handler for the exception does not exist exists
	</returns>
*************************************************************************************************/
int exception_uninstall_handler(unsigned int ls_exception_id)
{
	unsigned int CPU_ExceptionID = 0;
	for(; CPU_ExceptionID < MAX_CPU_EXCEPTIONS; CPU_ExceptionID++)
		if(i86_Exceptions[CPU_ExceptionID] == ls_exception_id) break;
	
	if(CPU_ExceptionID == MAX_CPU_EXCEPTIONS) return EXCEPTION_UNUSED;
	if(i86_Exceptions[CPU_ExceptionID] == LS_EXCEPT_RESERVED) return EXCEPTION_RESERVED;
	if(exception_handlers[CPU_ExceptionID] == 0) return EXCEPTION_DEFAULT_HANDLER;
	
    exception_handlers[CPU_ExceptionID] = 0;
	return 0;
}

/*************************************************************************************************
	<summary>exception_get_handler</summary>
	<para>gets a pointer to the handler function</para>
	<param name="ls_exception_id" type="unsigned int">exception id according to lindus-specifications/exceptions</param>
	<returns>
		EXCEPTION_UNUSED if the LS Exception is not supported/used by the architecture.
		EXCEPTION_RESERVED if the LS Exception is reserved by the architecture
		EXCEPTION_DEFAULT_HANDLER if a handler for the exception does not exist exists
		the address of the handler function if it exists, 0 if a handler does not exist
	</returns>
*************************************************************************************************/
void *exception_get_handler(unsigned int ls_exception_id)
{
	unsigned int CPU_ExceptionID = 0;
	for(; CPU_ExceptionID < MAX_CPU_EXCEPTIONS; CPU_ExceptionID++)
		if(i86_Exceptions[CPU_ExceptionID] == ls_exception_id) break;
	
	if(CPU_ExceptionID == MAX_CPU_EXCEPTIONS) return (void *)EXCEPTION_UNUSED;
	if(i86_Exceptions[CPU_ExceptionID] == LS_EXCEPT_RESERVED) return (void *)EXCEPTION_RESERVED;
	if(exception_handlers[CPU_ExceptionID] == 0) return (void *)EXCEPTION_DEFAULT_HANDLER;
	
	return exception_handlers[CPU_ExceptionID];
}