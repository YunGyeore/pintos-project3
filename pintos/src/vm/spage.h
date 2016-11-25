#ifndef VM_SPAGE_H
#define VM_SPAGE_H

#include <hash.h>
#include "filesys/file.h"

/* supplement page table entry structure */
struct spage_table_entry {
	struct file *file;
	off_t ofs;
	uint8_t *upage;
	uint32_t read_bytes;
	uint32_t zero_bytes;
	bool writable;
	struct hash_elem elem;
	int type;
};
struct spage_table_entry * get_ste(void *vaddr);
bool load_page (void *vaddr);
bool load_file (struct spage_table_entry *);
bool add_file (struct file *file, int32_t ofs, uint8_t *upage, uint32_t reqd_bytes, uint32_t zero_bytes, bool writable);

/* supplement page table hash function declaration */
unsigned spage_hash_func(const struct hash_elem *e, void *);
bool spage_less_func(const struct hash_elem *a, const struct hash_elem *b, void *);
void spage_action_func(struct hash_elem *e, void *aux);
#endif
