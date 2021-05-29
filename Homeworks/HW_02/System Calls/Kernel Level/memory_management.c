#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

SYSCALL_DEFINE1(allocate_mem, size_t, size){
	return (long int) kmalloc(size, GFP_KERNEL);
}


SYSCALL_DEFINE1(deallocate_mem, const void *, objp){
	kfree(objp);
}




