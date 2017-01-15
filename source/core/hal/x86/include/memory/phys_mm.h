/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Physical Memory Manager
//
//	phys_mm.h
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#ifndef _PHYS_MM_H
#define _PHYS_MM_H

#include <size_t.h>
#include <stdint.h>

/*==============================================================================================*/
// Interface Functions
/*==============================================================================================*/

extern uint32_t* pmm_init(size_t total_memory_kb, uint32_t *location);
extern void pmm_mmap_set_region(void *base, size_t size);
extern void pmm_mmap_unset_region(void *base, size_t size);
extern void pmm_refresh();
#endif // _PHYS_MM_H
