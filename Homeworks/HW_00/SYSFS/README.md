# SYSFS Module
## Requirements
Print all Parent Processes with a SYSFS Module

## Build and Load Module
* Create a ```Makefile``` (Makefile is included in this Repository)
* Compile with ```make``` and Load Module with ```sudo insmod sysfs_module.ko```
* Display Results with ```cat /sys/kernel/team00/find_roots```
