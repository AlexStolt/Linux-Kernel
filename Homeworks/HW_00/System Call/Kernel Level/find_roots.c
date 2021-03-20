#include <linux/sched.h>

// Get current pointer. Find real parent process pointer and pid. Do that    //
// iteratively until pid == 1.                                               //

SYSCALL_DEFINE0(find_roots){
  struct task_struct *curr_task;
  
  curr_task = current;
  
  printk("%s system call called by process %d", curr_task->comm, curr_task->pid);
  
  for(;; curr_task = curr_task->real_parent){
   
    printk("id: %d, name: %s", curr_task->pid, curr_task->comm);

    if (curr_task->pid == 1){
      break;
    }
  }
  return 0;
}
