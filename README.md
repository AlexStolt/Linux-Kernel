# C-OS
## Basic Packages
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
### Boot Options
```
cd /boot/
sudo mkinitramfs -o initrd.img-5.4.86-dev 5.4.86-dev
```
### [OPTIONAL] After Reboot
```sudo update-grub```
