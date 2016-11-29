#include "vm/swap.h"

void swap_init(void)
{
	sblock = block_get_role(BLOCK_SWAP);
	if(!sblock)
	{
		//printf("there is no swap device\n");
		return;
	}

	sbitmap = bitmap_create(block_size(sblock) / SECTOR_PER_PAGE);
	if(!sbitmap)
	{
		//pritf("initialize bitmap fail\n");
		return;
	}
	bitmap_set_all(sbitmap, S_AVAILABLE);
	lock_init(&slock);
}

size_t swap_out(void* frame)
{
	lock_acquire(&slock);
	size_t index_avail = bitmap_scan(sbitmap, 0, 1, S_AVAILABLE);

	if(index_avail == BITMAP_ERROR)
	{
		PANIC("there is no available swap slot!");
	}	

	bitmap_set(sbitmap, index_avail, S_USED);

	size_t i;
	for(i = 0; i<SECTOR_PER_PAGE; i++)
	{
		block_write(sblock, index_avail * SECTOR_PER_PAGE + i,
				(uint8_t *) frame + i * BLOCK_SECTOR_SIZE);
	}
	return index_avail;
}

void swap_in (size_t used_index, void* frame)
{
	lock_acquire(&slock);
	/*
	if(bitmap_test(sbitmap, used_index) == S_AVAILABLE)
	{
		lock_release(&slock);
		return;
	}*/
	bitmap_set(sbitmap, used_index, S_AVAILABLE);
	lock_release(&slock);
	size_t i;
	for( i=0; i<SECTOR_PER_PAGE; i++)
	{
	block_read(sblock, used_index * SECTOR_PER_PAGE + i,
		(uint8_t *) frame + i * BLOCK_SECTOR_SIZE);
	}
}
