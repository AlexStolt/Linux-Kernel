# C-OS
## Installation and Kernel Compilation
### Basic Packages
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
* GRUB_HIDDEN_TIMEOUT=-1
* GRUB_HIDDEN_TIMEOUT_QUIET=true
* GRUB_TIMEOUT=-1
### Compile Kernel and Install Modules
```
cd linux-5.4.86-dev/
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
3. **Prototypes**: ```ο /usr/src/linux-5.4.86-dev/include/linux/syscalls.h```
    * SYSCALL_DEFINE0(hello_syscall) -> asmlinkage long sys_hello_syscall(void);
4. **Syscall Number**: ```/usr/src/linux-5.4.86-dev/arch/x86/entry/syscalls/syscall_64.tbl```
    * ```436    common    hello_syscall    __x64_sys_hello_syscall```
