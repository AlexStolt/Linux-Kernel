# Homework 0x00
## System Call
### [Kernel and User Level Code](https://github.com/AlexStolt/Linux-Kernel/tree/main/Homeworks/HW_00/System%20Call)

### [User Level](https://github.com/AlexStolt/Linux-Kernel/tree/main/Homeworks/HW_00/System%20Call/User%20Level)
* Compile: ```make```
* Execute: ```./output```
* Display Output: ```dmesg | tail```
* Clean: ```make clean```


### [Kernel Module](https://github.com/AlexStolt/Linux-Kernel/tree/main/Homeworks/HW_00/Modules)
* How to Compile: Run ```make``` on Location Path 
* Load Module on Kernel: ```sudo insmod project1-kyber.ko``` on Location Path 
* How to Change Scheduler: ```sudo bash -c "echo team00_kyber > /sys/block/sda/queue/scheduler"```
* How to Test: Create a File and Write Something, then run ```dmesg | tail```
* How to Clean: Run ```make clean``` on Location Path

### [SYSFS Module](https://github.com/AlexStolt/Linux-Kernel/tree/main/Homeworks/HW_00/SYSFS)
Location Path: ```Final_Project_Submission/sysfs_module/```

* How to Compile: Run ```make``` on Location Path
* Load Module on Kernel: ```sudo insmod sysfs_module.ko``` on Location Path
* How to Test: Open File with ```cat /sys/kernel/team00/find_roots```
* How to Clean: Run ```make clean``` on Location Path
