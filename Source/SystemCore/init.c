/********************************************************************************/
//Lindus Kernel Initialization Script
//Author  :   Yashas Samaga
//Date    :   21-04-2012
//Description: Function "init_system" is called from the "entry.asm".This is 
//             responsible for the initialization of other components.
//
//Copyright (C) Yashas Samaga <yashas_2010@yahoo.com>
/********************************************************************************/
#include <system.h>
#include <arch\x86.h>
#include <init.h>
#include <drivers\tm\screen.h>
//////////////////////////////////////////////////////////////////////////////////
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

///////////////////////////////////////////////
int init_system ()
{
	init_console();
	
	
	for(;;);
}