#include <sys/syscall.h>
#include <unistd.h>
#include "memory.h"

long allocate_mem(size_t size){
	return(syscall(__NR_allocate_mem, size));
}
