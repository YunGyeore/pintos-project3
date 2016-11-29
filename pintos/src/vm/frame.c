#include "threads/malloc.h"
#include "threads/palloc.h"
#include "vm/frame.h"

/* frame table hash function */ 
static unsigned frame_hash_func(const struct hash_elem *e, void *aux UNUSED); 
static bool frame_less_func(const struct hash_elem *a, const struct hash_elem *b, void *aux UNUSED); 
static void frame_action_func(struct hash_elem *e, void *aux UNUSED);

/* frame table hash function definition */

/* hash function for frame table */
static unsigned frame_hash_func(const struct hash_elem *e, void *aux UNUSED)
{
        struct frame_table_entry *fte = hash_entry(e, struct frame_table_entry, elem);
        return hash_int((int)fte->frame);
}

/* hash less function for frame table */
static bool frame_less_func(const struct hash_elem *a, const struct hash_elem *b, void *aux UNUSED)
{
        struct frame_table_entry *fa = hash_entry(a, struct frame_table_entry, elem);
        struct frame_table_entry *fb = hash_entry(b, struct frame_table_entry, elem);
        return fa->frame < fb->frame;
}

/* hash action function for frame table (hash destroy) */
static void frame_action_func(struct hash_elem *e, void *aux UNUSED)
{
        struct frame_table_entry *fte = hash_entry(e, struct frame_table_entry, elem);
        free(fte);
}


/* frame table operation function definition */
void frame_table_init(void)
{
        //list_init(&frame_table);
	hash_init(&frame_table, frame_hash_func, frame_less_func, NULL);
	lock_init(&frame_table_lock);
}

/* frame allocation */
void* frame_alloc(enum palloc_flags flags)
{
	if((flags & PAL_USER) == 0)
	{
		return NULL;
	}
	void *frame = palloc_get_page(flags); //if not success, it return NULL
	if(frame)
	{
		/* frame add to table */
		struct frame_table_entry *fte = malloc(sizeof(struct frame_table_entry));
       		fte->frame = frame;
       		fte->tid = thread_tid();

	        lock_acquire(&frame_table_lock);
	        hash_insert(&frame_table, &fte->elem);
	        lock_release(&frame_table_lock);
	}
	else 
	{
		if(!frame_evict()) //evict is not completely modified yet. why it need argument "frame"?
		{
			PANIC("eviction fail. swap is full!");
		}	
	}
	return frame;
}	
void frame_free(void *frame)
{
	struct frame_table_entry fte;
	struct hash_elem *e;
	fte.frame = frame;
	lock_acquire(&frame_table_lock);
	e = hash_find (&frame_table, &fte.elem);
	hash_delete(&frame_table, e);
	lock_release(&frame_table_lock);
}
bool frame_evict(void)
{
	return false;
}
