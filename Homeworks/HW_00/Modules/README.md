# Module
## block/kyber-iosched.c
### Modify block/kyber-iosched.c
* Copy to ```~/project1_module/```
* Rename ```kyber-iosched.c``` to ```project1-kyber.c```
* Modify ```project1-kyber.c```
* Create a ```Makefile``` (Makefile is included in this File)
* Compile with ```make``` and Load Module with ```sudo insmod project1-kyber.ko```
  * Current Scheduler: ```cat /sys/block/sda/queue/scheduler``` -> ```[mq-deadline] team00_kyber none```
* Modify Scheduler to Test ```sudo bash -c "echo team00_kyber > /sys/block/sda/queue/scheduler"```
  * Current Scheduler: ```mq-deadline [team00_kyber] none```
* Testing Module 
  1. Create a File with Nano or Vim
  2. Write a String Of Characters
  3. Save File and Exit
  4. ```dmesg | tail``` with Expected Output ```In team00_kyber_dispatch_request function```
* Reset Scheduler: ```sudo bash -c "echo mq-deadline > /sys/block/sda/queue/scheduler"```
