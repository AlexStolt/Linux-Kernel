#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
   
  
SYSCALL_DEFINE0(slob_get_total_alloc_mem){
	return allocated_page_memory;
}
  
SYSCALL_DEFINE0(slob_get_total_free_mem){
     return total_unused_memory;     
}     
