View Debug Output
------------------------------
1. Open schedule.c
2. Add #define DEBUG
3. Compile and Execute


Hide Debug Output
------------------------------
1. Open schedule.c
2. Remove #define DEBUG (if it exists)
3. Compile and Execute


Measurements Output Pipes
------------------------------
1. Each Process CPU Clock Ticks Measurements are Printed on stderr
2. Mean Time to Completion is also Printed on stderr 
3. Debug Output is Printed on stdout


Changing Scheduling Policy
------------------------------
1. Scheduling based on Process Goodness
  i.    Open schedule.c 
  ii.   Add #define GOODNESS
  iii.  Compile and Execute
2. Scheduling based on Process Expected Burst
  i.    Open schedule.c 
  ii.   Remove or Comment Out #define GOODNESS (if it exists)
  iii.  Compile and Execute


How to Compile
------------------------------
1. Go to Scheduler_VM Path
2. make

How to Execute
------------------------------
1. Hiding Measurements of Each Process and Mean Time to Completion from stdout and Saving Them to a File  
  i.  Go to Scheduler_VM Path and Run ./sjf_sched <INPUT.conf> 2>STDERR_OUTPUT.txt
  ii. Terminal Outputs all Scheduling Information
  ii. View Measurements Information with cat STDERR_OUTPUT.txt

2. Output all Information with Measurements
  i. Go to Scheduler_VM Path and Run ./sjf_sched <INPUT.conf>


[NOTES]
1. For the Submitted Scheduler
  i.  Scheduling Policy is based on Goodness
  ii. Debug Output will be Printed on stdout