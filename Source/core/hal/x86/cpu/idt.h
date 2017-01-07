/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Processor Interface
//	Global Descriptor Table Implementations
//
//	idt.h
//	Provides an interface to work with processor's IDT.
//
//	Date: January 6th 2017
//
/*************************************************************************************************/
#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

/*==============================================================================================*/
// Interface Defines
/*==============================================================================================*/
#define MAX_INTERRUPTS 256

#define IDT_DESC_TYPE_TSK_32				0x05
#define IDT_DESC_TYPE_INT_16				0x06
#define IDT_DESC_TYPE_TRP_16				0x07
#define IDT_DESC_TYPE_INT_32				0x0E
#define IDT_DESC_TYPE_TRP_32				0x0F
#define IDT_DESC_DPL_RING0					0x00
#define IDT_DESC_DPL_RING3					(0x20 | 0x40)
#define IDT_DESC_PRESENT					0x80

/*==============================================================================================*/
// Interface Structures
/*==============================================================================================*/
struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

/*==============================================================================================*/
// Interface Function Prototypes
/*==============================================================================================*/
extern struct idt_entry* idt_get_descriptor (uint32_t i);
extern void idt_set_descriptor(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
extern void initilize_idt();

#endif // _IDT_H
