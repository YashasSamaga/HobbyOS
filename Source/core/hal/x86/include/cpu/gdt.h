/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Processor Interface
//	Global Descriptor Table Implementations
//
//	gdt.c
//	Provides an interface to work with processor's GDT.
//
//	Date: January 6th 2017
//
/*************************************************************************************************/
#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>

/*==============================================================================================*/
// Interface Defines
/*==============================================================================================*/
#define MAX_DESCRIPTORS	3

// descriptor adresses
#define CODE_DESC 							0x08
#define DATA_DESC 							0x10

// descriptor flags
#define	GDT_DESC_FLAG_ACCESS 				0x01
#define	GDT_DESC_FLAG_DATA_READONLY 		0x00
#define	GDT_DESC_FLAG_DATA_READWRITE 		0x02
#define	GDT_DESC_FLAG_CODE_EXEC 			0x00
#define	GDT_DESC_FLAG_CODE_READEXEC			0x02
#define	GDT_DESC_FLAG_EXPANSION_DAT_UP 		0x00
#define	GDT_DESC_FLAG_EXPANSION_DAT_DOWN 	0x04
#define	GDT_DESC_FLAG_CODE_CONFORM 			0x04
#define	GDT_DESC_FLAG_DATA_SEGMENT 			0x00
#define	GDT_DESC_FLAG_CODE_SEGMENT 			0x08
#define	GDT_DESC_FLAG_SYSTEM_DESC 			0x00
#define	GDT_DESC_FLAG_CODEDATA 				0x10
#define GDT_DESC_DPL_RING0					0x00
#define GDT_DESC_DPL_RING3					(0x20 | 0x40)
#define	GDT_DESC_FLAG_PRESENT_MEM 			0x80

// descriptor granularity flags (first 8 bits)
#define	GDT_DESC_GRAN_4K  					0x80
#define	GDT_DESC_GRAN_NONE 					0x00
#define	GDT_DESC_TYPE_32 					0x40
#define	GDT_DESC_TYPE_16 					0x00	

/*==============================================================================================*/
// Interface Structures
/*==============================================================================================*/
struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

/*==============================================================================================*/
// Interface Function Prototypes
/*==============================================================================================*/
extern struct gdt_entry* gdt_get_descriptor (uint32_t i);
extern void gdt_set_descriptor(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
extern void initilize_gdt();

#endif // _GDT_H
