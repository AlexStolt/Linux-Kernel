# Homework 0

## Task 0
Location Path: ```./System\ Call/```

* How to Compile: Run ```make``` on Location Path
* How to Run: Run ```./output``` on Location Path
* How to Test: Run ```dmesg | tail```
* How to Clean: Run ```make clean``` on Location Path

## Task 1

Location Path: ```./Modules/```

* How to Compile: Run ```make``` on Location Path 
* Load Module on Kernel: ```sudo insmod project1-kyber.ko``` on Location Path 
* How to Change Scheduler: ```sudo bash -c "echo team00_kyber > /sys/block/sda/queue/scheduler"```
* How to Test: Create a File and Write Something, then run ```dmesg | tail```
* How to Clean: Run ```make clean``` on Location Path

## Task 2
Location Path: ```./SYSFS/```

* How to Compile: Run ```make``` on Location Path
* Load Module on Kernel: ```sudo insmod sysfs_module.ko``` on Location Path
* How to Test: Open File with ```cat /sys/kernel/team00/find_roots```
* How to Clean: Run ```make clean``` on Location Path

## Final Submission
Our Final Homework Submission
