#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int priority;
    int burst_time;
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
    // Sort the processes by priority (higher priority first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int total_time = 0;
    float total_waiting_time = 0.0;
    float total_burst_time = 0.0;
    float total_turnaround_time = 0.0;

    printf("----------------------------------------------------------------------\n");
    printf("| Process | Priority | Burst Time | Waiting Time | Turnaround Time   |\n");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int waiting_time = total_time;
        int turnaround_time = waiting_time + processes[i].burst_time;
        printf("|    %2d   |    %2d    |     %3d    |      %3d      |        %3d       |\n",
               processes[i].process_id,
               processes[i].priority,
               processes[i].burst_time,
               waiting_time, turnaround_time);
        total_time += processes[i].burst_time;
        total_waiting_time += waiting_time;
        total_burst_time += processes[i].burst_time;
        total_turnaround_time += turnaround_time;
    }

    printf("----------------------------------------------------------------------\n");

    float avg_waiting_time = total_waiting_time / n;
    float avg_burst_time = total_burst_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Burst Time = %.2f\n", avg_burst_time);
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);

    
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    priorityScheduling(processes, n);
    printf("Sahib Preet Singh AI-ML OO713211621\n");
    return 0;
}
