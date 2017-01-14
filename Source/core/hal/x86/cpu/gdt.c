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
#include <stdint.h>

#include <hal.h>
#include <cpu/cpu.h>
#include <cpu/gdt.h>

/*==============================================================================================*/
// Structures/Enumerations (Private)
/*==============================================================================================*/
struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
static struct
{
	struct gdt_entry entries[MAX_DESCRIPTORS];
	struct gdt_ptr gdtr;
} gdt;
/*==============================================================================================*/
// Interface Functions
/*==============================================================================================*/
/*************************************************************************************************
	<summary>gdt_get_descriptor</summary>
	<para>gets the pointer to the asked descriptor</para>
	<param name="idx" type="unsigned int">GDT descriptor index</param>
	<remarks>the pointer returned points to the "real" descriptor in the memory</remarks>
	<returns>a pointer to the descriptor (gdt_entry *)</returns>
*************************************************************************************************/
struct gdt_entry* gdt_get_descriptor (unsigned int idx) 
{
	return &gdt.entries[idx];
}

/*************************************************************************************************
	<summary>gdt_set_descriptor</summary>
	<para>sets a GDT descriptor</para>
	<param name="num" type="unsigned int">GDT descriptor index</param>
	<param name="base" type="uint32_t">segment base address</param>
	<param name="limit" type="uint32_t">segment limit</param>
	<param name="access" type="uint8_t">access flags</param>
	<param name="gran" type="uint8_t">granularity flags</param>
	<remarks>refer to cpu.h for the list of flags</remarks>
*************************************************************************************************/
void gdt_set_descriptor(unsigned int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt.entries[num].base_low = (base & 0xFFFF);
    gdt.entries[num].base_middle = (base >> 16) & 0xFF;
    gdt.entries[num].base_high = (base >> 24) & 0xFF;

    gdt.entries[num].limit_low = (limit & 0xFFFF);
    gdt.entries[num].granularity = ((limit >> 16) & 0x0F);

    gdt.entries[num].granularity |= (gran & 0xF0);
    gdt.entries[num].access = access;
}

/*************************************************************************************************
	<summary>initilize_gdt</summary>
	<para>installs HAL's new GDT</para>
*************************************************************************************************/
void initilize_gdt()
{
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
    gdt.gdtr.limit = (sizeof(struct gdt_entry) * MAX_DESCRIPTORS) - 1;
    gdt.gdtr.base = (uint32_t)&gdt.entries;
	
	// set GDTR processor register
	__asm__ __volatile__ ("lgdt %0" : : "m"(gdt.gdtr) : "memory");
}
