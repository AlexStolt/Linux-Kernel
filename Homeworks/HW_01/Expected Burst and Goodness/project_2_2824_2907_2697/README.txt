STOLTIDIS ALEXANDROS 	(stalexandros@uth.gr)	2824
KOUTSOUKIS NIKOLAOS 	(nkoutsoukis@uth.gr)	2907
KYRITSIS SPYROS 	(kyspyridon@uth.gr)	2697



View Debug Output
------------------------------
1. Open schedule.c
2. Add #define DEBUG
3. Compile and Execute


Hide Debug Output
------------------------------
1. Open schedule.c
2. Remove #define DEBUG
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
  ii.   Remove or Comment Out #define GOODNESS
  iii.  Compile and Execute


Configuration Files
------------------------------
1. Required Files Path
  i. configs/basic/
    * interactive.conf (tests interactive processes with children)
    * non_interactive.conf (tests non-interactive processes with children)
    * complex.conf (tests both interactive and non-interactive processes)
2. Not Required Files
  i. configs/additional
    * noninteractive/ (non-interactive processes)	
    * interactive/    (interactive processes)
    * complex/	(complex processes)  
  ii. configs/seed_validation (configs that test interactive processes with different seeds)
3. Round Robin (scripts for round robin calculations on configs/round_robin_configs/)
Results
------------------------------
Results can be found on the MS-Excel Spreadsheet

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
