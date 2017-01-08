/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	CPU Exception Mangement
//
//	exceptions.h
//	Interface to work with CPU Exception handlers.
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <stdint.h>

/*==============================================================================================*/
// Defines and Enumerations
/*==============================================================================================*/
#define MAX_CPU_EXCEPTIONS 32

enum 
{
	EXCEPTION_UNUSED = 1,
	EXCEPTION_RESERVED,
	EXCEPTION_HANDLER_EXISTS,
	EXCEPTION_DEFAULT_HANDLER
};

/*==============================================================================================*/
// Interface Function Prototypes
/*==============================================================================================*/
extern int exception_install_handler(unsigned int ls_exception_id, void (*handler)());
extern int exception_uninstall_handler(unsigned int ls_exception_id);
extern void *exception_get_handler(unsigned int ls_exception_id);

#endif // _EXCEPTIONS_H
