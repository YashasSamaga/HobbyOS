/******************************************************************************/
//	CPU Exception Constants
//
//	ls-exceptions.h
//	Each type of exception is assigned a fixed constant which does NOT vary over
//	architecture. Every hardware abstraction layer designed for a particular
//	architecture must convert the exception ids mentioned in this include to
// 	the architecture specific ids for operating the hardware. All interface 
//	functions MUST use the exception ids mentioned in this include.
//
//	Date: January 8th 2017
//
/******************************************************************************/
#ifndef _LS_EXCEPTIONS_H
#define _LS_EXCEPTIONS_H

enum LS_EXCEPTIONS
{
	LS_EXCEPT_RESERVED = 0,
	LS_EXCEPT_DIV_BY_ZERO = 1,
	LS_EXCEPT_DEBUG = 2,			
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
	LS_EXCEPT_X87_FPU,
	LS_EXCEPT_ALIGNMENT_CHECK,
	LS_EXCEPT_MACHINE_CHECK,
	LS_EXCEPT_SIMD_FPU,
	LS_EXCEPT_VIRTUALIZATION,
	LS_EXCEPT_TRIPLE_FAULT,
	LS_EXCEPT_FPU_ERROR_INT	
};

#endif // _LS_EXCEPTIONS_H
