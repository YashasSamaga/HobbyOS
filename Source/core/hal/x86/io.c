/******************************************************************************/
//	Basic IN/OUT instructions
//	Hardware Abstraction Layer x86
//
//	Implementations to access hardware ports (input/output)
//
//	io.c
//	Date: January 6th 2017
//
/******************************************************************************/
#include "hal.h"
#include <hal.h>

uint8_t inportb (uint16_t _port)
{
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


