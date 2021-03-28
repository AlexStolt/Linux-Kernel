#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/printk.h>


static struct kobject *example_kobject;
volatile int roots = 0;

static ssize_t find_roots(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
  int buff_write_len = 0;
  struct task_struct *curr_task = current;


  buff_write_len += sprintf(buf,"find_roots sysfs opened by process %d\n", curr_task->pid);
  
   for(;; curr_task = curr_task->real_parent){
   
    buff_write_len += sprintf(buf + strlen(buf), "id: %d, name: %s\n", curr_task->pid, curr_task->comm);
    
    if (curr_task->pid == 1){
      break;
    }
  }

  return buff_write_len;
}


struct kobj_attribute find_roots_attribute = __ATTR(find_roots, 0660, find_roots, NULL);

static int __init mymodule_init(void){
  int error = 0;

  example_kobject = kobject_create_and_add("team00", kernel_kobj);
  if(!example_kobject)
    return -ENOMEM;
  
  error = sysfs_create_file(example_kobject, &find_roots_attribute.attr);
  
  if(error){
    printk("failed to create the foo file in /sys/kernel/kobject_example\n");
  }
  return error;
}


static void __exit mymodule_exit(void){
  printk("Module uninitialized successfully\n");
  kobject_put(example_kobject);
}

module_init(mymodule_init);
module_exit(mymodule_exit);
MODULE_LICENSE("GPL");
