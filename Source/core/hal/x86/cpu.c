/******************************************************************************/
//	Hardware Abstraction Layer x86
//	Processor Interface
//
//	cpu.c
//	Date: January 6th 2017
//
/******************************************************************************/

#include "hal.h"
#include "cpu.h"
#include <hal.h>
#include <string.h>

struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[MAX_DESCRIPTORS];
struct gdt_ptr gdtr;

static struct idt_entry	idt [MAX_INTERRUPTS];
static struct idt_ptr idtr;

extern void fault_handler();
void fault_handler () 
{
	printf("\nUnhandled Exception\n");
	for(;;);
}

struct gdt_entry* gdt_get_descriptor (uint32_t i) 
{
	return &gdt[i];
}
struct idt_entry* idt_get_descriptor (uint32_t i) 
{
	return &idt[i];
}

void gdt_set_descriptor(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void idt_set_descriptor(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

int cpu_initialize () 
{
	/* Global Descriptor Table Initilization */
	// null descriptor
    gdt_set_descriptor(0, 0, 0, 0, 0);   
	
	// code descriptor
    gdt_set_descriptor(1, 0, 0xFFFFFFFF, 
	GDT_DESC_FLAG_CODE_READEXEC | GDT_DESC_FLAG_CODE_SEGMENT | GDT_DESC_FLAG_CODEDATA | GDT_DESC_DPL_RING0 | GDT_DESC_FLAG_PRESENT_MEM, 
	GDT_DESC_GRAN_4K | GDT_DESC_TYPE_32);
	
	// data descriptor
    gdt_set_descriptor(2, 0, 0xFFFFFFFF, 
	GDT_DESC_FLAG_DATA_READWRITE | GDT_DESC_FLAG_CODEDATA | GDT_DESC_DPL_RING0 | GDT_DESC_FLAG_PRESENT_MEM,
	GDT_DESC_GRAN_4K | GDT_DESC_TYPE_32);	

	// set GDT pointer
    gdtr.limit = (sizeof(struct gdt_entry) * MAX_DESCRIPTORS) - 1;
    gdtr.base = (uint32_t)&gdt;
	
	// set GDTR processor register
	__asm__ __volatile__ ("lgdt %0" : : "m"(gdtr) : "memory");
	
	
	/* Interrupt Descriptor Table Initilization */
	// set default handlers
	extern void default_handler();
	for(int i = 0; i < MAX_INTERRUPTS; i++)
		idt_set_descriptor(i, (unsigned)default_handler, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	
	// set IDT pointer
	idtr.limit = (sizeof (struct idt_entry) * MAX_INTERRUPTS) - 1;
    idtr.base = (uint32_t)&idt;
	
	// set IDTR processor register
	__asm__ __volatile__ ("lidt %0" : : "m"(idtr) : "memory");	
	return 0;
}

void cpu_shutdown () 
{

}
