#include <sys/syscall.h>
#include <unistd.h>
#include "memory.h"

void deallocate_mem(void * objp){
	syscall(__NR_deallocate_mem, objp);
}
