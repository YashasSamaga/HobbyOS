/************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//
//	The hardware abstraction layer provides an 'abstract' hardware independent interface to 
// 	control the hardware from the kernel. The hardware abstraction layer is the first component
// 	to be loaded by the bootloader. The hardware abstraction layer is responsible for initilizing
//  the basic devices and controllers after which control is transfered to the kernel.
//
//	hal.c
//	Hardware abstraction layer implementation code	
//
//	Date: January 6th 2017
//
/************************************************************************************************/
#include <stdint.h>

#include <hal.h>
#include <irq.h>
#include <cpu/cpu.h>
#include <cpu/exceptions.h>
#include <chips/pic-i8259.h>
#include <chips/pit-i8253.h>
#include <memory/phys_mm.h>

/*===============================================================================================*/
// Defines and Enumerations (Private)
/*===============================================================================================*/
enum
{
	FREE_MEMORY = 1,
	RESERVED_MEMORY,
	ACPI_RECLAIMABLE_MEMORY,
	ACPI_NVS_MEMORY,
	BAD_MEMORY	
};

/*===============================================================================================*/
// Implementation Structures/Enumerations (Private)
/*===============================================================================================*/
struct memory_map_entry
{
	uint32_t baseLow;
	uint32_t baseHigh;
	uint32_t sizeLow;
	uint32_t sizeHigh;
	uint32_t type;
	uint32_t acpi_extended_attribute;
};

struct bootInfo_t
{
	uint32_t memoryLow;
	uint32_t memoryHigh_KB;
	uint32_t mmap_addr;
	uint32_t mmap_entries;
	uint32_t imageSize;
	uint32_t load_addr;
};

/*===============================================================================================*/
// Implementation Functions (Private)
/*===============================================================================================*/
/*************************************************************************************************
	<summary>hal_shutdown</summary>
	<para>carries out the shutdown processes</para>
*************************************************************************************************/
int hal_shutdown() 
{
	cpu_shutdown();
	return 0;
}

/*************************************************************************************************
	<summary>hal_initialize</summary>
	<para>initilizes the hardware abstraction layer</para>
	<remarks> 
		* entry point of the HAL (called from start wrapper in init.asm)
		* calls the kernel after HAL initilization
	</remarks>
*************************************************************************************************/
void hal_initialize(struct bootInfo_t *bootInfo) 
{	
	//void* used_upto = 
	pmm_init(bootInfo->memoryLow + bootInfo->memoryHigh_KB*64 + 1024, (void*)(bootInfo->load_addr + bootInfo->imageSize));
	
	struct memory_map_entry* memory_map = (struct memory_map_entry*)bootInfo->mmap_addr;
	for (uint32_t i = 0; i < bootInfo->mmap_entries; i++) 
		if(memory_map[i].type == FREE_MEMORY) 
			pmm_mmap_unset_region((void*)memory_map[i].baseLow, memory_map[i].sizeLow);
	
	// first 1MB of memory contains important data which must be protected
	pmm_mmap_set_region((void*)0, 1024 * 1024);
	
	// reserve 16MB of memory from the start of the kernel
	pmm_mmap_set_region((void*)bootInfo->load_addr, 16 * 1024 * 1024);
	
	// build the LIFO free blocks stack
	pmm_refresh();
	
	cpu_initialize();
	
	// remap IRQs so that they won't trigger exceptions for hardware interrupts
	pic_initialize(MAX_CPU_EXCEPTIONS, MAX_CPU_EXCEPTIONS + 8);
	pit_initialize();
	irq_enable();
	
	//HAL initilized, execute kernel_init()
	extern int kernel_init();
	if(kernel_init() == 1) hal_shutdown (); // something went wrong, shutdown the computer
	
	for(;;);
}


