#ifndef VM_SWAP_H
#define VM_SWAP_H

#include "devices/block.h"
#include "threads/vaddr.h"
#include "threads/synch.h"
#include <bitmap.h>

#define S_AVAILABLE 0
#define S_USED 1

#define SECTOR_PER_PAGE (PGSIZE /BLOCK_SECTOR_SIZE)

struct lock slock;
struct block* sblock;
struct bitmap* sbitmap;

void swap_init(void);
size_t swap_out(void* frame);
void swap_in(size_t used_index, void* frame);

#endif
