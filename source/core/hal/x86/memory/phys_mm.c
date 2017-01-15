/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Physical Memory Manager
//
//	phys_mm.h
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#include <stdint.h>
#include <size_t.h>
#include <string.h>

#include <hal.h>
#include <memory/phys_mm.h>

/*==============================================================================================*/
// Defines and Enumerations (Private)
/*==============================================================================================*/
#define BLOCK_SIZE	4096

#define SetBlockBit(x) physical_memory_bitmap[x/32] |= (1<<(x%32))
#define UnsetBlockBit(x) physical_memory_bitmap[x/32] &= ~(1<<(x%32))
#define TestBlockBit(x) physical_memory_bitmap[x/32] & (1<<(x%32))

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/

// stores free blocks in a stack
uint32_t *free_block_stack;
int free_block_pos = 0;

// stores a
uint32_t *physical_memory_bitmap;
uint32_t block_sets_total = 0;
uint32_t blocks_total = 0;

uint32_t total_memory = 0;

/*==============================================================================================*/
// Interface Functions (Private)
/*==============================================================================================*/
uint32_t* pmm_init(size_t total_memory_kb, uint32_t *location)
{	
	physical_memory_bitmap = location;	
	total_memory = total_memory_kb * 1024;
	blocks_total = (total_memory/BLOCK_SIZE) + 1;
	block_sets_total = blocks_total/32;
	
	free_block_stack = physical_memory_bitmap + (blocks_total/32) + 1;
	
	memset(physical_memory_bitmap, 0xFF, block_sets_total*4);
	return (free_block_stack + blocks_total);
}

void pmm_refresh()
{
	free_block_pos = -1;
	for(uint32_t i = 0; i < block_sets_total; i++)
	{
		if(physical_memory_bitmap[i] == 0xFFFFFFFF) continue;
		uint32_t block_set = physical_memory_bitmap[i];
		for(uint32_t j = 0; j < sizeof(uint32_t)*8; j++)
			if(!(block_set & (1<<j)))
				free_block_stack[free_block_pos++] = (i * sizeof(uint32_t) * 8) + j;
	}
}

/* used during initilization only */
void pmm_mmap_set_region(void *base, size_t size)
{
	if(size == 0) return;
	
	int block_start = (uint32_t)base/4096;
	int block_end = (uint32_t)(base + size)/4096;
	int block_cur = block_start;
	
	while(block_cur <= block_end)
	{
		SetBlockBit(block_cur);
		block_cur++;
	}
}
/* used during initilization only */
void pmm_mmap_unset_region(void *base, size_t size)
{
	if(size == 0) return;
	
	int block_end = (uint32_t)(base + size)/4096;
	int block_start = (uint32_t)(base)/4096;
	int block_cur = block_start;
	
	while(block_cur <= block_end)
	{
		UnsetBlockBit(block_cur);
		block_cur++;
	}
}

int pmmngr_alloc_block (void** addr)
{
	if (free_block_pos == 0)
		return 0;	//out of memory

	int frame = free_block_stack[free_block_pos--];
	SetBlockBit(frame);

	*addr = (void*)(frame * BLOCK_SIZE);	
	return 1;
}

void pmmngr_free_block (void* addr)
{
	int frame = (uint32_t)addr/BLOCK_SIZE;

	UnsetBlockBit(frame);	
	free_block_stack[++free_block_pos] = frame;
}
