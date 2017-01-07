/******************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Processor Interface
//
//	cpu.h
//	Date: January 6th 2017
//
/******************************************************************************/
#ifndef _CPU_H
#define _CPU_H

#include<stdint.h>

#define MAX_DESCRIPTORS	3

#define CODE_DESC 							0x08
#define DATA_DESC 							0x10

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
	
#define	GDT_DESC_GRAN_4K  					0x80
#define	GDT_DESC_GRAN_NONE 					0x00
#define	GDT_DESC_TYPE_32 					0x40
#define	GDT_DESC_TYPE_16 					0x00	

#define MAX_INTERRUPTS 256

#define IDT_DESC_TYPE_TSK_32				0x05
#define IDT_DESC_TYPE_INT_16				0x06
#define IDT_DESC_TYPE_TRP_16				0x07
#define IDT_DESC_TYPE_INT_32				0x0E
#define IDT_DESC_TYPE_TRP_32				0x0F
#define IDT_DESC_DPL_RING0					0x00
#define IDT_DESC_DPL_RING3					(0x20 | 0x40)
#define IDT_DESC_PRESENT					0x80

struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

typedef void (*IRQ_HANDLER)(void);

struct _R32BIT 
{
    uint32_t eax, ebx, ecx, edx, esi, edi, ebp, esp, eflags;
    uint8_t cflag;
};

struct _R16BIT 
{
    uint16_t ax, bx, cx, dx, si, di, bp, sp, es, cs, ss, ds, flags;
    uint8_t cflag;
};

struct _R16BIT32 
{
    uint16_t ax, axh, bx, bxh, cx, cxh, dx, dxh;
	uint16_t si, di, bp, sp, es, cs, ss, ds, flags;
	uint8_t cflags;
};

struct _R8BIT 
{
    uint8_t al, ah, bl, bh, cl, ch, dl, dh;
};

struct _R8BIT32 
{
    uint8_t al, ah; uint16_t axh; 
	uint8_t bl, bh; uint16_t bxh; 
	uint8_t cl, ch; uint16_t cxh; 
	uint8_t dl, dh; uint16_t dxh; 
};

union _INTR16 
{
    struct _R16BIT x;
    struct _R8BIT h;
};

union _INTR32 
{
	struct _R32BIT x;
	struct _R16BIT32 l;
	struct _R8BIT32 h;
};

extern int cpu_initialize ();
extern void cpu_shutdown ();

extern struct gdt_entry* gdt_get_descriptor (uint32_t i); 
extern struct idt_entry* idt_get_descriptor (uint32_t i); 
extern void gdt_set_descriptor(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
extern void idt_set_descriptor(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
#endif // _CPU_H
