#include <sys/syscall.h>
#include <unistd.h>
#include "roots.h"

int find_roots_syscall_wrapper(void){
    return (syscall(__NR_find_roots));
}
