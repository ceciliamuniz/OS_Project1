#include <stdio.h>
#include <stdlib.h>


// Shortest Job First (SJF) Scheduling Algorithm Implementation in C
// This program reads process data from a file, sorts the processes based on arrival time and burst time,
// calculates waiting time and turnaround time, and prints the Gantt chart along with average times.

// Structure to represent a process
typedef struct {
    int pid; // Process ID
    int at;  // Arrival time
    int bt;  // Burst time
    int priority;  // Priority
} Process;

// Function to calculate waiting time
void findWaitingTimeSJF(Process processes[], int n, int wt[]) {
    int service_time[n];
    service_time[0] = processes[0].at;  // First process starts at arrival time
    wt[0] = 0;  // First process has no waiting time

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + processes[i - 1].bt;
        wt[i] = service_time[i] - processes[i].at;

        // Ensure waiting time is not negative
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

// Function to calculate turn around time (TAT)
// TAT = Burst Time + Waiting Time
void findTurnAroundTimeSJF(Process processes[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = processes[i].bt + wt[i];
    }
}

// Function to print Gantt Chart
void printGanttChartSJF(Process processes[], int n) {
    printf("\nGantt Chart for SJF:\n");

    // Top border
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    // Process Execution Order
    int time = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt / 2; j++) printf(" "); // Centering
        printf("P%d", processes[i].pid);
        for (int j = 0; j < processes[i].bt / 2; j++) printf(" "); // Centering
        printf("|");
        time += processes[i].bt;
    }
    printf("\n ");

    // Bottom border
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    // Timeline
    time = 0;
    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt; j++) printf("  ");
        time += processes[i].bt;
        printf("%d", time);
    }
    printf("\n");
}

// Function to calculate and display average times
void findavgTimeSJF(Process processes[], int n) {
    // Initialize waiting time (wt) and turnaround time (tat) arrays
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTimeSJF(processes, n, wt);
    findTurnAroundTimeSJF(processes, n, wt, tat);

    // Display process details
    printf("\nProcess ID  Arrival Time  Burst Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d         %d            %d            %d             %d\n", 
               processes[i].pid, processes[i].at, processes[i].bt, wt[i], tat[i]);
    }

    // Calculate and display average WT and TAT
    // Ensure we don't divide by zero if no processes are present
    if (n > 0) {
        printf("\nAverage WT (waiting time) for SJF = %.3f", (float)total_wt / n);
        printf("\nAverage TAT (turnaround time) for SJF = %.3f\n", (float)total_tat / n);
    } else {
        printf("\nError: No valid processes were read from the file.\n");
    }

    // Print Gantt Chart
    printGanttChartSJF(processes, n);
}

// Function to compare processes by arrival time first, then by burst time
int compareProcess(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    // First compare by Arrival Time (earliest arrives first)
    if (p1->at != p2->at) {
        return p1->at - p2->at;  // Earliest arrival time comes first
    }

    // If Arrival Time is the same, compare by Burst Time (shortest burst time first)
    return p1->bt - p2->bt;
}

// Main function
int main() {
    FILE *file = fopen("processes.txt", "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    // Skip the header line
    char header[100];
    fgets(header, sizeof(header), file);

    Process processes[100];
    int n = 0;

    // Read the actual process data
    while (fscanf(file, "%d %d %d %d", &processes[n].pid, &processes[n].at, &processes[n].bt, &processes[n].priority) == 4) {
        n++;
    }

    // Sort processes by Arrival Time first, then by Burst Time (for SJF)
    qsort(processes, n, sizeof(Process), compareProcess);

    printf("\nScheduling using SJF:\n");

    // Calculate average time and print Gantt chart
    findavgTimeSJF(processes, n);

    fclose(file);
    return 0;
}
