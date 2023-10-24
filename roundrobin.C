#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
};

// Function to perform Round Robin Scheduling
void roundRobinScheduling(struct Process processes[], int n, int time_quantum) {
    int remaining_time[n];
    int waiting_time[n];
    int turnaround_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    int total_time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= time_quantum) {
                    total_time += remaining_time[i];
                    waiting_time[i] = total_time - processes[i].burst_time;
                    turnaround_time[i] = total_time;
                    remaining_time[i] = 0;
                    completed++;
                } else {
                    total_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
    }

    printf("-------------------------------------------------------------\n");
    printf("| Process | Burst Time  |  Waiting Time  |  Turnaround Time |\n");
    printf("-------------------------------------------------------------\n");

    float total_waiting_time = 0.0;
    float total_burst_time = 0.0;
    float total_turnaround_time = 0.0;

    for (int i = 0; i < n; i++) {
        printf("|    %2d   |     %3d     |      %3d      |        %3d        |\n",
               processes[i].process_id,
               processes[i].burst_time,
               waiting_time[i], turnaround_time[i]);
        total_waiting_time += waiting_time[i];
        total_burst_time += processes[i].burst_time;
        total_turnaround_time += turnaround_time[i];
    }

    printf("-------------------------------------------------------------\n");

    float avg_waiting_time = total_waiting_time / n;
    float avg_burst_time = total_burst_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Burst Time = %.2f\n", avg_burst_time);
    printf("Average Turnaround Time = %.2f\n");
    
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    int time_quantum;
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    roundRobinScheduling(processes, n, time_quantum);
    printf("Sahib Preet Singh AI-ML OO713211621\n");
    return 0;
}
