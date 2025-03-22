# OS_Project1
# CPU Scheduling Simulator

## Overview
This program implements First-Come, First-Served (FCFS) and Shortest Job First (SJF) scheduling algorithms to simulate CPU process scheduling. It reads process data from a file, sorts them based on arrival time, and schedules them according to the selected algorithm.

## Features
- Implements **First-Come, First-Served (FCFS)** scheduling.
- Implements **Shortest Job First (SJF)** scheduling (non-preemptive).
- Reads process data from a file.
- Computes and displays:
  - Waiting Time (WT)
  - Turnaround Time (TAT)
  - Gantt Chart visualization.
- Calculates average WT and TAT for performance evaluation.

## Input Format
The program reads process information from a file named `processes.txt`, which should be structured as follows:
```
PID Arrival_Time Burst_Time Priority
1         0           5        1
2         2           3        2
3         4           1        3
```
- **PID**: Unique identifier for the process.
- **Arrival_Time**: Time when the process arrives in the system.
- **Burst_Time**: Execution time required for the process.


## Sample Output
```
Scheduling using FCFS:
Process ID  Arrival Time  Burst Time  Waiting Time  Turnaround Time
1          0            5            0             5
2          2            3            3             6
3          4            1            4             5

Average WT (waiting time) = 2.33
Average TAT (turnaround time) = 5.33

Gantt Chart:
| P1 | P2 | P3 |
0    5    8    9
```


