#include "userprog/syscall.h"
#include <user/syscall.h>
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "devices/shutdown.h"
#include "threads/synch.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#define ARG(type, i) *(type *)arg[i]


struct owned_file
{
	int fd;
	struct file *file;
	struct list_elem elem;
};

struct lock file_lock;
const int argc[13] = {0, 1, 1, 1, 2, 1, 1, 1, 3, 3, 2, 1, 1};

struct owned_file * find_owned_file(int);
static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
//////////////////////////////////////////////////////////////////////////////
	lock_init(&file_lock);
//////////////////////////////////////////////////////////////////////////////
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{

//////////////////////////////////////////////////////////////////////////////
	int syscall_number, fd;
	void *arg[3];
	void * paddr, *vaddr;
	unsigned size, i;
//	printf("esp : %x\n", f->esp);
	check_address(f->esp); // ppack jong, To do
	syscall_number = *((int*)f->esp);

	if(syscall_number == SYS_HALT) shutdown_power_off();
	
	get_argument(f->esp, arg, argc[syscall_number]);
//	printf("syscall %d\n", syscall_number);	
	switch(syscall_number){
		/* Process control syscall */
		case SYS_EXIT:
			exit(ARG(int, 0));
			break;
		case SYS_EXEC:
			check_address(ARG(const char *, 0));
//			printf("vaddr : %x\n", ARG(const void*, 0));
            paddr = pagedir_get_page(thread_current()->pagedir, ARG(const void *, 0));
            if(paddr == NULL){
					exit(-1);
			}
			f->eax = exec((const char*)paddr);
			break;
		case SYS_WAIT:
			f->eax = wait(ARG(pid_t, 0));
			break;

		/* File system syscall */
		case SYS_CREATE:
			check_address(ARG(const char *, 0));
			paddr = pagedir_get_page(thread_current()->pagedir, ARG(const void *, 0));
			if(paddr == NULL) exit(-1);
			lock_acquire(&file_lock);
			f->eax = create((const char *)paddr, ARG(unsigned, 1));
			lock_release(&file_lock);
			break;
		case SYS_REMOVE:
			check_address(ARG(const char *, 0));
                        paddr = pagedir_get_page(thread_current()->pagedir, ARG(const void *, 0));
                        if(paddr == NULL) exit(-1);
			
			lock_acquire(&file_lock);
			f->eax = remove((const char *)paddr);
			lock_release(&file_lock);
			break;
		case SYS_OPEN:
			check_address(ARG(const char *, 0));
                        paddr = pagedir_get_page(thread_current()->pagedir, ARG(const void *, 0));
                        if(paddr == NULL) exit(-1);

			lock_acquire(&file_lock);
			f->eax = open((const char *)paddr);
			lock_release(&file_lock);
			break;
		case SYS_FILESIZE:
			lock_acquire(&file_lock);
			f->eax = filesize(ARG(int, 0));
			lock_release(&file_lock);
			break;
		case SYS_READ:

			size = ARG(unsigned, 2);
			vaddr = ARG(void *, 1); 
			for(i=0 ; i<size ; i++){
				check_address((char *)vaddr + i); // string address check
			}
			paddr = pagedir_get_page(thread_current()->pagedir, (const void *)vaddr);
			if(paddr==NULL) exit(-1);
			fd = ARG(int, 0);
			if(fd == STDIN_FILENO){
				for(i=0 ; i<size ; i++)
					((char *)paddr)[i] = input_getc();
				f->eax = size;
			}
			else {
					lock_acquire(&file_lock);
					f->eax = read(fd, paddr, size);
					lock_release(&file_lock);
			}
			break;
		case SYS_WRITE:
			size = ARG(unsigned, 2);
			vaddr = ARG(void *, 1);
			for(i=0 ; i<size ; i++){
					check_address((char *)vaddr + i); // string address check
			}
			paddr = pagedir_get_page(thread_current()->pagedir, (const void *)vaddr);
			if(paddr==NULL) exit(-1);
			fd = ARG(int, 0);
			if(fd == STDOUT_FILENO){
					//printf("\n%x thread file list size : %d\n", thread_current(), list_size(&thread_current()->file_list));
					putbuf((const void *)paddr, size);
					f->eax = size;
			}
			else {
				lock_acquire(&file_lock);
				f->eax = write(fd, (const void *)paddr, size);
				lock_release(&file_lock);
			}
			break;
		case SYS_SEEK:
			lock_acquire(&file_lock);
			seek(ARG(int, 0), ARG(unsigned, 1));
			lock_release(&file_lock);
			break;
		case SYS_TELL:
			lock_acquire(&file_lock);
			f->eax = tell(ARG(int, 0));
			lock_release(&file_lock);
			break;
		case SYS_CLOSE:
			lock_acquire(&file_lock);
			close(ARG(int, 0));
			lock_release(&file_lock);
			break;
		default:
			break;
	} 
//////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////
void
check_address(void *address)
{
	if(is_user_vaddr((const void *)address) && address >= (void *)0x08048000) //To do
		return;
	exit(-1);
}
void
get_argument(void *esp, void **arg, int cnt)
{
	int i;
	esp = (void*)((int*)esp + 1);
	for(i=0 ; i<cnt ; i++, esp=(void*)((int*)esp + 1))
	{
		check_address(esp);
		arg[i] = esp;
	}
}



/*file syscall*/
bool
create (const char *file, unsigned initial_size)
{
        return filesys_create(file, initial_size);
}

bool
remove (const char *file)
{
	return filesys_remove(file);
}

int
open (const char *file)
{
	struct thread * current_thread = thread_current();
	struct owned_file *new_file;
	struct file *result = filesys_open(file);
	if(!result) return -1;
	new_file = (struct owned_file *)malloc(sizeof(struct owned_file));
	new_file->fd = (current_thread->fd++);
	new_file->file = result;
	list_push_back(&current_thread->file_list, &new_file->elem);
	return new_file->fd;
}

int
filesize (int fd)
{
	struct owned_file *file = find_owned_file(fd);
	if(!file) return -1;
	return file_length(file->file);
}

int
read (int fd, void *buffer, unsigned size)
{
	struct owned_file * file = find_owned_file(fd);
	if(!file) return -1;
	return file_read(file->file, buffer, size);
}

int
write (int fd, const void *buffer, unsigned size)
{
	struct owned_file * file = find_owned_file(fd);
	if(!file) return -1;
	return file_write(file->file, buffer, size);
}

	void
seek (int fd, unsigned position)
{
	struct owned_file *seeked_file= find_owned_file(fd);
	if(seeked_file==NULL) return;
	file_seek(seeked_file->file, position);
}

	unsigned
tell (int fd)
{
	struct owned_file *seeked_file= find_owned_file(fd);
	if(seeked_file==NULL) return -1;
	return file_tell(seeked_file);
}

void
close (int fd)
{
	if(fd == -1) // close all of the files
	{
		struct thread * current_thread = thread_current();
		struct list_elem *i;
		struct owned_file * file;
		while(!list_empty(&current_thread->file_list)){
			i = list_front(&current_thread->file_list);
			file = list_entry(i, struct owned_file, elem);
//			printf("thread %d close fd : %d\n", current_thread->tid, file->fd);
			file_close(file->file);
			list_remove(&file->elem);
			free(file);
		}
	}
	else
	{
		struct owned_file * file = find_owned_file(fd);
		if(!file) return;
		file_close(file->file);
		list_remove(&file->elem);
		free (file);
	}
}

/*process syscall*/
pid_t
exec (const char *cmd_line)
{
        return process_execute(cmd_line);
}

int
wait (pid_t pid)
{
        return process_wait(pid);
}
void
exit (int status)
{
        struct thread * current_thread = thread_current();
        current_thread->exit_status = status;
//      printf("\nexit : %d\n", status);        
        lock_acquire(&file_lock);
        close(-1);
        lock_release(&file_lock);
//      printf("\nfile closes!\n");
        while(!list_empty(&current_thread->child_list))
        {
                list_pop_front(&current_thread->child_list);
        }
//      printf("\nchild list free!\n");
        sema_up(&current_thread->zombie_sema);
//      printf("\nexit process zombie semaphore up!\n");
        printf("%s: exit(%d)\n", current_thread->name, current_thread->exit_status);
        thread_exit();
        return;
}
struct owned_file *
find_owned_file(int fd){

	struct thread* t =thread_current();
	struct list_elem *e;

	e=list_begin(&t->file_list);

	while(e != list_end(&t->file_list))
	{
		struct owned_file *of = list_entry(e, struct owned_file ,elem);

		if(fd == of->fd) return of;

		e=list_next(e);
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////

