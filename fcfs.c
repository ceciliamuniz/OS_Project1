#include <stdio.h>

// Function to calculate waiting time
void findWaitingTimeFCFS(int processes[], int n, int bt[], int at[], int wt[]) {
    int service_time[n];
    service_time[0] = at[0];  // First process starts at arrival time
    wt[0] = 0;  // First process has no waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + bt[i - 1];
        wt[i] = service_time[i] - at[i];

        // Ensure waiting time is not negative
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

// Function to calculate turn around time (TAT)
void findTurnAroundTimeFCFS(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to print Gantt Chart
void printGanttChartFCFS(int processes[], int n, int bt[], int at[]) {
    printf("\nGantt Chart for FCFS:\n");

    // Top border
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    // Process Execution Order
    int time = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i] / 2; j++) printf(" "); // Centering
        printf("P%d", processes[i]);
        for (int j = 0; j < bt[i] / 2; j++) printf(" "); // Centering
        printf("|");
        time += bt[i];
    }
    printf("\n ");

    // Bottom border
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    // Timeline
    time = 0;
    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("  ");
        time += bt[i];
        printf("%d", time);
    }
    printf("\n");
}

// Function to calculate and display average times
void findavgTimeFCFS(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTimeFCFS(processes, n, bt, at, wt);
    findTurnAroundTimeFCFS(processes, n, bt, wt, tat);

    // Display process details
    printf("\nProcess ID  Arrival Time  Burst Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d         %d            %d            %d             %d\n", 
               processes[i], at[i], bt[i], wt[i], tat[i]);
    }

    // Calculate and display average WT and TAT
    // Ensure we don't divide by zero if no processes are present
    if (n > 0) {
      printf("\nAverage WT (waiting time) = %.3f", (float)total_wt / n);
      printf("\nAverage TAT (turnaround time) = %.3f\n", (float)total_tat / n);
    } else {
      printf("\nError: No valid processes were read from the file.\n");
    }

    // Print Gantt Chart
    printGanttChartFCFS(processes, n, bt, at);
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

  int processes[100], at[100], bt[100], priority[100], n = 0;

  // Read the actual process data
  while (fscanf(file, "%d %d %d %d", &processes[n], &at[n], &bt[n], &priority[n]) == 4) {
      n++;
  }

  // Sort processes by Arrival Time (FCFS scheduling)
  for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
          if (at[i] > at[j]) {  // If arrival time of process i is greater than j, swap them
              // Swap process ID
              int temp = processes[i];
              processes[i] = processes[j];
              processes[j] = temp;

              // Swap Arrival Time
              temp = at[i];
              at[i] = at[j];
              at[j] = temp;

              // Swap Burst Time
              temp = bt[i];
              bt[i] = bt[j];
              bt[j] = temp;

              // Swap Priority (if needed, though not used in FCFS)
              temp = priority[i];
              priority[i] = priority[j];
              priority[j] = temp;
          }
      }
  }

  // Call scheduling function
  printf("\nScheduling using FCFS:\n");
  findavgTimeFCFS(processes, n, bt, at);

  return 0;
}
