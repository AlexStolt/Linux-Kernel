#include <stdio.h>
#include "memory.h"

int main(){
	void *p = (void *) allocate_mem(10000);
	
	printf("Address of Memory Allocation: %p\n", p);
	
	deallocate_mem(p);
	return 0;

}
