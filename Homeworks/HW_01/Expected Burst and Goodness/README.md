# Expected Burst and Goodness Based Schedulers

## How to Compile
1. Go to ```Expected Burst and Goodness/``` Path
2. make

## How to Execute
### Export Measurements of Each Process to a File
1. Run ```./sjf_sched <INPUT.conf> 2>STDERR_OUTPUT.txt```
2. Terminal Outputs all Scheduling Information
3. View Measurements Information with ```cat STDERR_OUTPUT.txt```

### Output all Information with Measurements
  * Run ```./sjf_sched <INPUT.conf>```

## View Debug Output
1. Open schedule.c
2. Add #define DEBUG
3. Compile and Execute

## Hide Debug Output
1. Open schedule.c
2. Remove ```#define DEBUG```
3. Compile and Execute

## Measurements Output Pipes
1. Each Process CPU Clock Ticks Measurements are Printed on stderr
2. Mean Time to Completion is also Printed on stderr 
3. Debug Output is Printed on stdout

## Changing Scheduling Policy
* Scheduling based on Process Goodness
  *  Open schedule.c 
  *  Add ```#define GOODNESS```
  *  Compile and Execute
* Scheduling based on Process Expected Burst
  *   Open schedule.c 
  *   ***Remove*** ```#define GOODNESS```
  *   Compile and Execute
  
## Testing with Configuration Files
### Configuration Files
1. Required Files Path
    1. **configs/basic/**
        1. **interactive.conf** (tests interactive processes with children)
        2. **non_interactive.conf** (tests non-interactive processes with children)
        3. **complex.conf** (tests both interactive and non-interactive processes)
2. Not Required Files
    1. **configs/additional**
        1. **noninteractive/** (non-interactive processes)	
        1. **interactive/**    (interactive processes)
        3. **complex/**	(complex processes)  
    2. **configs/seed_validation** (configs that test interactive processes with different seeds)
3. Round Robin (scripts for round robin calculations on configs/round_robin_configs/)
