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
#include <cpu\cpu.h>
#include <cpu\exceptions.h>
#include <chips\pic-i8259.h>
#include <chips\pit-i8253.h>

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

struct memory_map_entry
{
	uint32_t startLow;
	uint32_t startHigh;
	uint32_t sizeLow;
	uint32_t sizeHigh;
	uint32_t type;
	uint32_t acpi_extended_attribute;
};
struct bootInfo_t
{
	uint32_t memoryLow;
	uint32_t memoryHigh;
	uint32_t mmap_addr;
	uint32_t mmap_entries;
};
/*************************************************************************************************
	<summary>hal_initialize</summary>
	<para>initilizes the hardware abstraction layer</para>
	<remarks> 
		* entry point of the kernel (called from start wrapper in init.asm)
		* calls the kernel after HAL initilization
	</remarks>
*************************************************************************************************/
void hal_initialize(struct bootInfo_t *bootInfo) 
{	
	struct memory_map_entry* region = (struct memory_map_entry*)bootInfo->mmap_addr;
	
	cpu_initialize();
	// remap IRQs so that they won't trigger exceptions
	pic_initialize(MAX_CPU_EXCEPTIONS, MAX_CPU_EXCEPTIONS + 8);
	pit_initialize();
	irq_enable();
	
	//HAL initilized, execute kernel_init()
	extern int kernel_init();
	if(kernel_init() == 1) hal_shutdown (); // something went wrong, shutdown the computer
	
	for(;;);
}


