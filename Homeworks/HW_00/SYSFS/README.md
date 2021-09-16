# SYSFS Module
## Requirements
Print all Parent Processes with a SYSFS Module

## Build and Load Module
* Create a ```Makefile``` (Makefile is included in this Repository)
* How to Compile: Run ```make``` on Location Path
* Load Module on Kernel: ```sudo insmod sysfs_module.ko``` on Location Path
* How to Test: Open File with ```cat /sys/kernel/team00/find_roots```
* How to Clean: Run ```make clean``` on Location Path
