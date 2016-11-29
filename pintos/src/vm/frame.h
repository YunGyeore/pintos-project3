#ifndef VM_FRAME_H
#define VM_FRAME_H
#include "threads/thread.h"
#include "threads/synch.h"
#include "vm/spage.h"
#include <hash.h>
struct hash frame_table;
struct lock frame_table_lock;
struct frame_table_entry
{
	struct spage_table_entry *ste;
	void *frame;
	tid_t tid;
	struct hash_elem elem;
};

void * frame_alloc(enum palloc_flags flags, struct spage_table_entry *);
void frame_free(void *frame);
bool frame_evict();


/* declaration */
void frame_table_init(void);


#endif
