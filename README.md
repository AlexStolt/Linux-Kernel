# C-OS
## Installation and Kernel Compilation
### Basic Packages
```sudo apt-get update```

```sudo apt-get install build-essential libncurses-dev flex bison libssl-dev```
### Kernel
```
cd /usr/src
sudo wget https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.4.86.tar.gz
sudo tar -C /usr/src -xvf linux-5.4.86.tar.gz
sudo mv linux-5.4.86 linux-5.4.86-orig
sudo cp -R linux-5.4.86-orig linux-5.4.86-dev
```
### Grub Configuration
```sudo nano /etc/default/grub```
#### Update If Option Exists
* ```GRUB_HIDDEN_TIMEOUT=-1```
* ```GRUB_HIDDEN_TIMEOUT_QUIET=true```
* ```GRUB_TIMEOUT=-1```
### Compile Kernel and Install Modules
```
cd /usr/src/linux-5.4.86-dev/
sudo make localmodconfig
sudo make menuconfig
sudo nano Makefile
```
#### Edit Makefile
* EXTRAVERSION = -dev
```
sudo make -j2
sudo make modules_install
sudo make install
```
### Boot (GRUB) Options Activation
```
cd /boot/
sudo mkinitramfs -o initrd.img-5.4.86-dev 5.4.86-dev
```
### [OPTIONAL] After Reboot
```sudo update-grub```

## System Paths
1. **C Files (*.c)**: ```/usr/src/linux-5.4.86-dev/kernel/```
2. **Object Files (*.o)**: ```/usr/src/linux-5.4.86-dev/kernel/Makefile```
3. **Prototypes**: ```/usr/src/linux-5.4.86-dev/include/linux/syscalls.h```
    * Example: ```SYSCALL_DEFINE0(hello_syscall)``` should be converted to ```asmlinkage long sys_hello_syscall(void);```
4. **Syscall Number**: ```/usr/src/linux-5.4.86-dev/arch/x86/entry/syscalls/syscall_64.tbl```
    * Example: ```436    common    hello_syscall    __x64_sys_hello_syscall```
5. Compile Kernel
6. **Syscall Definition**: ```/usr/src/linux-5.4.86-dev/arch/x86/include/generated/uapi/asm/unistd_64.h```
   * ```#define __NR_hello_syscall 436```
7. **Make Syscall Visible to User**: Copy ```/usr/src/linux-5.4.86-dev/arch/x86/include/generated/uapi/asm/unistd_64.h``` to ```/usr/include/x86_64-linux-gnu/asm```
8. Compile Kernel
9. **View Syscall**: ```/boot/System.map-5.4.86-dev```
   * ```grep "hello_syscall" /boot/System.map-5.4.86-dev```

## Testing Kernel Syscall from User Level
1. Create a Header File: ```syscall_wrapper.h```
```
int hello_syscall_wrapper(void)
```
2. Create C System Call Wrapper: ```syscall_wrapper.c```
```
#include "syscall_wrapper.h"
int hello_syscall_wrapper(void) {
   return syscall(__NR_hello_syscall)
}
```
3. Create a **Static Library**: ```libhello_syscall_wrapper.a```
```
 gcc -c syscall_wrapper.c -o syscall_wrapper.o
 ar rcs libhello_syscall_wrapper.a syscall_wrapper.o
 ```
4. Write a Main Entry Point: ```main.c```
5. Compile Main and Connect to Library
```
gcc -c main.c -o main.o
gcc main.o -L. -lhello_syscall_wrapper
```
6. Results (printf()): ```dmesg```

## Modules
### Layout
```
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("DualBSD/GPL");

static int hello_init(void){
   printk(KERN_ALERT "Hello,world\n");
   return 0;
}

static void hello_exit(void){
   printk(KERN_ALERT "Goodbye,cruelworld\n");
}

module_init(hello_init);
module_exit(hello_exit);
```

### Makefile
```
obj-m := module_name.o
module-objs := file_1.o file_2.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
        $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
        rm -f *.o *.ko *.mod.c *.mod *.order *.symvers
```
### Load Module to Kernel
```sudo insmod module.ko```
#### Show Loaded Modules
```lsmod``` or ```lsmod | grep module```
### Remove Module from Kernel
```sudo rmmod module.ko```
