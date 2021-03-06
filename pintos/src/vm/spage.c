#include "threads/palloc.h"
#include "threads/malloc.h"
#include "vm/spage.h"
#include "threads/thread.h"
#include "userprog/process.h"
#include "vm/frame.h"
#include "threads/vaddr.h"
/* function definition for supplement page table */
/* hash func */
unsigned spage_hash_func(const struct hash_elem *e, void *aux)
{
	struct spage_table_entry *ste = hash_entry(e, struct spage_table_entry, elem);
	return hash_int((int) ste->upage);
}
bool spage_less_func(const struct hash_elem *a, const struct hash_elem *b, void *aux)
{
	struct spage_table_entry *sa = hash_entry(a, struct spage_table_entry, elem);
	struct spage_table_entry *sb = hash_entry(b, struct spage_table_entry, elem);
	return sa->upage < sb->upage;
}
void spage_action_func(struct hash_elem *e, void *aux)
{
	struct spage_table_entry *ste = hash_entry(e, struct spage_table_entry, elem);
	free(ste);
}

/* get supplement page of specific virtual user address */
struct spage_table_entry * get_ste(void *vaddr)
{
	struct thread * cur = thread_current();
	struct spage_table_entry ste;
	ste.upage = pg_round_down(vaddr);
	struct hash_elem *e = hash_find(&cur->spage_table, &ste.elem);
	return (!e)?NULL:hash_entry(e, struct spage_table_entry, elem);
}
/* load page for lazy loading */
bool load_page (void *vaddr)
{
	struct spage_table_entry *ste = get_ste(vaddr);
	if(!ste) return false;
	switch (ste->type)
	{
		case 0:
			return load_file(ste);
		case 1:
			return false; //load_swap(ste);
		case 2:
			return load_file(ste);
		default:
			break;
	}	
}

/* load file */
bool load_file (struct spage_table_entry *ste)
{
	//	void *addr = pagedir_get_page(thread_current()->pagedir, ste->upage);
	void *kpage = frame_alloc(PAL_USER, ste);
	int read_b;
	if (kpage == NULL)
		return false;

	/* Load this page. */
	//	printf("file : %x and size : %d\n", ste->file, file_length(ste->file));
	read_b = file_read_at (ste->file, kpage, ste->read_bytes, ste->ofs);
	if (read_b != (int) ste->read_bytes)
	{
//		printf("actual read bytes : %d\n", read_b);
//				printf("file pointer : %x\nallocated page : %x\nread_byte : %d\noffset : %d\n", ste->file, kpage, ste->read_bytes, ste->ofs);
		//          palloc_free_page (kpage);                   /*original version*/
		frame_free (kpage);                     /* our implementation */
		return false;
	}
	memset (kpage + ste->read_bytes, 0, ste->zero_bytes);

	/* Add the page to the process's address space. */
	if (!install_page (ste->upage, kpage, ste->writable))
	{
		//          palloc_free_page (kpage);                   /*original version*/
		frame_free (kpage);                     /*our implementation */
		return false;
	}
	ste->loaded = true;
	return true;
}
bool add_file (struct file *file, int32_t ofs, uint8_t *upage, uint32_t read_bytes, uint32_t zero_bytes, bool writable)
{
	struct thread * cur = thread_current();
	struct spage_table_entry *ste = (struct page_table_entry *)malloc(sizeof(struct spage_table_entry));
	if(!ste) return false;
	ste->file = file;
	ste->ofs = ofs;
	ste->upage = upage;
	ste->read_bytes = read_bytes;
	ste->zero_bytes = zero_bytes;
	ste->writable = writable;
	ste->type = 0;
	ste->loaded = false;
	if(hash_insert(&cur->spage_table, &ste->elem)==NULL)
		return true;
	else
		return false;
}


bool grow_stack(void *vaddr)
{
	void *paged_vaddr = pg_round_down(vaddr);
	if((PHYS_BASE - paged_vaddr) >MAX_STACK)  return false;

	struct spage_table_entry *spt_entry = malloc(sizeof(struct spage_table_entry));
	if(!spt_entry) return false;

	else
	{
		spt_entry->upage = paged_vaddr;
		spt_entry->type = 1; //SWAP == 1 
	}

	uint8_t *frame = frame_alloc(PAL_USER, spt_entry);

	if(frame == NULL)
	{
		free(spt_entry);
		return false;
	}

	bool install_page_success = install_page(spt_entry -> upage, frame, true);
	/////////////////install_page _ what return?
	if(install_page_success == false)
	{
		free(spt_entry);
		frame_free(frame);
		return false;
	}
	bool hash_check = (hash_insert(&thread_current() -> spage_table, &spt_entry->elem)==NULL);
	return hash_check;
}


