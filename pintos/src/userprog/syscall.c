#include "userprog/syscall.h"
#include "userprog/process.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/thread.h"
#include "threads/init.h"
#include <string.h>
#include "threads/malloc.h"
#include "threads/vaddr.h"
#include "filesys/file.h"
#include "devices/input.h"
#include "vm/frame.h"
#include "vm/spage.h"
#include "filesys/inode.h"
#define checkARG 	if((uint32_t)esp > 0xc0000000-(argsNum+1)*4) \
										syscall_exit(f,argsNum);
void delete_mmap_page(struct mmap_page *);

static void syscall_handler (struct intr_frame *);
static struct list fd_list;

struct lock FILELOCK;

int currentFd(struct thread *cur)
{
	struct list_elem *e = list_begin(&fd_list);
	int result = 0;
	for(;e!=list_end(&fd_list);e=list_next(e))
	{
		struct fd_elem *fe = list_entry(e,struct fd_elem, elem);
		if(fe->owner == cur)
			result++;
	}
	return result;
}

struct file* getFile(int fd, struct thread *cur)
{
	struct list_elem *e = list_begin(&fd_list);
	struct file* result = NULL;
	for(;e!=list_end(&fd_list);e=list_next(e))
	{
		struct fd_elem *fe = list_entry(e,struct fd_elem, elem);
		if(fe->owner == cur && fe->fd == fd)
		{
			result = fe->file;
			if(fe->isEXE)
				file_deny_write(fe->file);
			break;
		}
	}
	return result;
}
struct fd_elem* getFdElem(int fd, struct thread *cur)
{
        struct list_elem *e = list_begin(&fd_list);
        struct fd_elem * result = NULL;
        for(;e!=list_end(&fd_list);e=list_next(e))
        {
                struct fd_elem *fe = list_entry(e,struct fd_elem, elem);
                if(fe->owner == cur && fe->fd == fd)
                {
                        result = fe;
                        break;
                }
        }
        return result;
}

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
	list_init(&fd_list);
	lock_init(&FILELOCK);
}

static void
syscall_handler (struct intr_frame *f) 
{
	static int prev_esp=PHYS_BASE;
	static bool only_one = false;
	bool check = false;
	if( !only_one && (int)prev_esp - (int)f->esp > PGSIZE)
	{
		//      printf("\ncheck\n");
		struct spage_frame_table *spte = get_ste(f->esp);
		if(spte)
		{
			only_one=true;
			//              printf("\nin roop\n");
			int page_size = (prev_esp -(int)f->esp)/PGSIZE +1;
			int i;
			//              printf("\npage_size: %d\n",page_size);
			//printf("page_size: %d, f->esp: %x \n",page_size,f->esp);
			for(i=page_size -1; i>=1; i--)
			{
				check = grow_stack(f->esp+i*PGSIZE);
			}
		}
		//      if(!check){
		//      syscall_exit(f, -1);
		//      }
	}

	uint32_t syscall_num = *(uint32_t *)(f->esp);

	switch(syscall_num){
		case SYS_HALT: syscall_halt(f);                   /* Halt the operating system. */
									 break;
		case SYS_EXIT: syscall_exit(f,1);                   /* Terminate this process. */
									 break;
		case SYS_EXEC: syscall_exec(f,1);                   /* Start another process. */
									 break;
		case SYS_WAIT: syscall_wait(f,1);                   /* Wait for a child process to die. */
									 break;
		case SYS_CREATE: syscall_create(f,2);                 /* Create a file. */
										 break;
		case SYS_REMOVE: syscall_remove(f,1);                 /* Delete a file. */
										 break;
		case SYS_OPEN: syscall_open(f,1);                   /* Open a file. */
									 break;
		case SYS_FILESIZE: syscall_filesize(f,1);               /* Obtain a file's size. */
											 break;
		case SYS_READ:  syscall_read(f,3);                  /* Read from a file. */
										break;
		case SYS_WRITE: syscall_write(f,3);                  /* Write to a file. */
										break;
		case SYS_SEEK: syscall_seek(f,2);                   /* Change position in a file. */
									 break;
		case SYS_TELL: syscall_tell(f,1);                  /* Report current position in a file. */
									 break;
		case SYS_CLOSE: syscall_close(f,1);                 /* Close a file. */
										break;
		case SYS_MMAP: syscall_mmap(f, 2);
									 break;
		case SYS_MUNMAP: syscall_munmap(f, 1);
									break;
	}
}
void syscall_mmap(struct intr_frame *f, int argsNum)
{
//	printf("mmap!\n");
	struct thread * cur = thread_current();
	void * esp = f->esp;
        checkARG
		
        int fd = *(int *)(esp+4);
        void* addr = *(void **)(esp+8);
	if(addr>=0xbf800000 || addr<0x08048000){
		f->eax = -1; return;
	}
	if(fd == STDIN_FILENO || fd == STDOUT_FILENO){
		f->eax = -1;
		return;
	}
	struct fd_elem *fe = getFdElem(fd, cur);
	if(!fe || !addr)
	{
		f->eax = -1;
		return;
	}
	struct fild * file = file_reopen(fe->file);
	if((int)addr % (int)PGSIZE != 0){
		f->eax = -1;
		return;
	}
	off_t ofs=0;
	off_t read_bytes = file_length(file);

	if(read_bytes <= 0){
		f->eax = -1;
		return;
	}
	while(read_bytes>0){
		off_t read_page_bytes = (read_bytes > PGSIZE) ? PGSIZE : read_bytes;

		off_t zero_page_bytes = PGSIZE-read_page_bytes;
		struct spage_table_entry * ste = (struct spage_table_entry *)malloc(sizeof(struct spage_table_entry));
		if(!ste) {
			f->eax = -1; return;
		}
		struct mmap_page * mp = (struct mmap_page *)malloc(sizeof(struct mmap_page));
		if(!mp){
			free(ste);
			f->eax = -1; return;
		}//error
		ste->file = file;
		ste->ofs = ofs;
		ste->upage = addr;
		ste->read_bytes = read_page_bytes;
		ste->zero_bytes = zero_page_bytes;
		ste->type = 2;	 //mmap	
		ste->loaded = false;
		ste->writable = true;
		if(hash_insert(&cur->spage_table, &ste->elem) != NULL){
			free(ste); free(mp);
			f->eax = -1; return;
		}
		mp->id = cur->nextMapId;
		mp->ste = ste;
			
		list_push_back(&cur->mmap_file, &mp->elem);;
		read_bytes -= read_page_bytes;
		ofs += read_page_bytes;
		addr += read_page_bytes;
	}
	fe->mapid = cur->nextMapId;
	f->eax = cur->nextMapId++;
}
void syscall_munmap(struct intr_frame *f, int argsNum)
{
	void*esp = f->esp;
        checkARG

        int mapping = *(int *)(esp+4);
	munmap(mapping);
}
void munmap(int mapping)
{
	struct thread * cur = thread_current();
	struct list_elem *e = list_begin(&cur->mmap_file);
	
        for(;e!=list_end(&cur->mmap_file);e=list_next(e))
        {
                struct mmap_page *mp = list_entry(e,struct mmap_page, elem);
                if(mp->id == mapping)
                {
			e = list_prev(e);
                        delete_mmap_page(mp);
                }
        }
}
void allMunmap()
{
	struct thread * cur = thread_current();	
	struct list_elem *e = list_begin(&cur->mmap_file);
	for(;e!=list_end(&cur->mmap_file);e=list_next(e))
	{
		struct mmap_page *mp = list_entry(e,struct mmap_page, elem);
		e=list_prev(e); 
		delete_mmap_page(mp);
	}
}
void delete_mmap_page(struct mmap_page *mp)
{
	struct thread * cur = thread_current();
	struct spage_table_entry * ste = mp->ste;
	off_t write_b;
	if(ste->loaded){
		if(pagedir_is_dirty(cur->pagedir, ste->upage)){
			write_b = file_write_at(ste->file, ste->upage, ste->read_bytes, ste->ofs);
			
		}
		void * frame;
		frame = pagedir_get_page(cur->pagedir, ste->upage);
		frame_free(frame);
		pagedir_clear_page(cur->pagedir, ste->upage);
	}
	list_remove(&mp->elem);
	hash_delete(&cur->spage_table, &ste->elem);
	free(ste); free(mp);
}
void syscall_halt(struct intr_frame *f UNUSED)
{
	shutdown_power_off();
}

void allClose(struct thread *cur)
{
	struct list_elem *e = list_begin(&fd_list);
	for(;e!=list_end(&fd_list);e=list_next(e))
	{
		struct fd_elem *fe = list_entry(e,struct fd_elem, elem);
		if(fe->owner == cur)
		{
			file_close(fe->file);
			list_remove(e);	
			e=list_prev(e);
			free(fe);

		}
	}
}

void syscall_exit(struct intr_frame *f,int argsNum)
{
	void *esp = f->esp;
	struct thread *cur = thread_current(); 
	struct child_info *ci = getCIFromTid(cur->tid);
	int status;

	if(argsNum != -1)		// by kernel
	{
		if((uint32_t)esp > 0xc0000000-(argsNum+1)*4){					// bad arg address
			status = -1;
		} else {
			status = *(int *)(esp+4);
		}
	} else status = -1;

	if(ci != NULL){
		ci->exitCode = status;
	}
	allMunmap();
	if(FILELOCK.holder != cur)
	lock_acquire(&FILELOCK);
	allClose(cur);
	if(FILELOCK.holder == cur)
	lock_release(&FILELOCK);
	printf("%s: exit(%d)\n",cur->name,status);
	
	thread_exit();
}

void syscall_exec(struct intr_frame *f,int argsNum)
{
	void *esp = f->esp;
	
	checkARG

	char* command_line = *(char**)(esp+4);

	char buf[16];
	char *ptrptr;
	strlcpy(buf,command_line,16);
	strtok_r(buf," ",&ptrptr);

	if(filesys_open(buf) == NULL)
	{
		f->eax = -1;
		return;
	}

	tid_t tid = process_execute(command_line);	

	if(tid == TID_ERROR)
	{
		f->eax = -1;
		return;
	}


	struct child_info * ci = getCIFromTid(tid);

	sema_down(&ci->e_sema);
	
	if(ci->loadFail)
	{
		f->eax = -1;	
	return;
	}

	f->eax = tid;
	return;
}

void syscall_wait(struct intr_frame *f,int argsNum)
{
	void *esp = f->esp;

	checkARG

	tid_t tid = *(tid_t *)(esp+4);

	f->eax = process_wait(tid);
}

void syscall_create(struct intr_frame *f,int argsNum){
	void*esp = f->esp;
	checkARG
	
	char* file = *(char **)(esp+4);
	uint32_t initial_size = *(uint32_t *)(esp+8);
	
	if(strlen(file) <= 0)
	{
		f->eax = 0;
		return;
	}
	lock_acquire(&FILELOCK);
	bool result = filesys_create(file,initial_size);
	lock_release(&FILELOCK);
	f->eax = (int)result;
}
void syscall_remove(struct intr_frame *f,int argsNum){

	void*esp = f->esp;
	checkARG

	char* file = *(char **)(esp+4);
	
	lock_acquire(&FILELOCK);
	bool result = filesys_remove(file);
	lock_release(&FILELOCK);
	f->eax = (int)result;

}


void syscall_open(struct intr_frame *f,int argsNum){

	void*esp = f->esp;
	checkARG

	char* filename = *(char **)(esp+4);

	if(filename == NULL){
		f->eax = -1;
		return;
	}

	struct thread *cur = thread_current();
	
	lock_acquire(&FILELOCK);
	struct file* file = filesys_open(filename);

	if(file != NULL){
		struct fd_elem *fe = (struct fd_elem *)malloc(sizeof(struct fd_elem));
	
		fe->owner = cur;
		fe->file = file;
		fe->fd = currentFd(fe->owner)+2;	// above 2
		fe->filename = filename;
		if(checkIsThread(filename))
		{
			fe->isEXE = true;
		} else fe->isEXE = false;
		
		fe->mapid = -1;
		list_push_back(&fd_list,&fe->elem);
		
		f->eax = fe->fd;
	} else f->eax = -1;
	lock_release(&FILELOCK);
}

void syscall_filesize(struct intr_frame *f,int argsNum){

	void*esp = f->esp;
	checkARG
	
	int fd = *(int *)(esp+4);

	lock_acquire(&FILELOCK);
	struct file *file = getFile(fd,thread_current());
	if(file != NULL)
		f->eax = file_length(file);
	else f->eax = -1;
	lock_release(&FILELOCK);
}

void syscall_read(struct intr_frame *f,int argsNum){

	void*esp = f->esp;
	checkARG

	int fd = *(int *)(esp+4);
	char* buffer = *(char **)(esp+8);
	uint32_t size = *(uint32_t *)(esp+12);
	
	if(buffer>(unsigned int)0xc0000000) syscall_exit(f,-1);
	lock_acquire(&FILELOCK);
	if(fd == 0){
		uint32_t i;
		for(i = 0; i < size; i++)
		{
			buffer[i] = input_getc();		
		}
		f->eax = size;
	} else if(fd == 1){
		f->eax = -1;
	} else {
		struct file *file = getFile(fd,thread_current());
		if (file != NULL)
		{
			if(file_tell(file) >= file_length(file))
				f->eax = 0;
			else f->eax = file_read(file,buffer,size);
		}
		else f->eax = -1;
	}
	lock_release(&FILELOCK);
}

void syscall_write (struct intr_frame *f,int argsNum)
{
	void* esp = f->esp;

	checkARG

	int fd = *(int *)(esp+4);
	char* buffer = *(char **)(esp+8);
	uint32_t size = *(uint32_t *)(esp+12);
	lock_acquire(&FILELOCK);
	if (fd == 1)
	{
		putbuf((char *)buffer,size);
		f->eax = size;
	} else if (fd == 0){
		f->eax = -1;
	} else {
		struct file *file = getFile(fd,thread_current());
		if (file != NULL)
		{
			if(file_tell(file) >= file_length(file))	// EOF
				f->eax = 0;
			else f->eax = file_write(file,buffer,size);
		}
		else f->eax = -1;
	}
	lock_release(&FILELOCK);
}



void syscall_seek(struct intr_frame *f,int argsNum){
	void*esp = f->esp;
	checkARG

	int fd = *(int *)(esp+4);
	uint32_t position = *(uint32_t *)(esp+8);

	lock_acquire(&FILELOCK);
	struct file *file = getFile(fd,thread_current());
	if(file != NULL)
	{
		file_seek(file,position);		
	}

	lock_release(&FILELOCK);
}
void syscall_tell(struct intr_frame *f,int argsNum){
	void*esp = f->esp;
	checkARG

	int fd = *(int *)(esp+4);

	lock_acquire(&FILELOCK);
	struct file *file = getFile(fd,thread_current());
	if(file != NULL)
	{
		f->eax = file_tell(file);
	} else f->eax = -1;
	lock_release(&FILELOCK);
	
}

void elemFile(struct file *file)
{
	struct list_elem *e = list_begin(&fd_list);
	for(;e!=list_end(&fd_list);e=list_next(e))
	{
		struct fd_elem *fe = list_entry(e,struct fd_elem, elem);
		if(fe->file == file && fe->owner == thread_current())
		{
			list_remove(e);
			free(fe);
			return;
		}
	}
}

void syscall_close(struct intr_frame *f,int argsNum){
	void*esp = f->esp;
	checkARG

	int fd = *(int *)(esp+4);


	struct thread* cur = thread_current();
	struct fd_elem *fe = getFdElem(fd, cur);
	if(fe == NULL) return;
	struct file *file = fe->file;
	lock_acquire(&FILELOCK);
	if(file != NULL)
	{	
		file_close(file);
		elemFile(file);
	}
	lock_release(&FILELOCK);
}
