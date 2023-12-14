
#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform SJF scheduling
void sjfScheduling(struct Process processes[], int n) {
    // Sort the processes by arrival time (if arrival times are the same, sort by burst time)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time ||
                (processes[j].arrival_time == processes[j + 1].arrival_time && processes[j].burst_time > processes[j + 1].burst_time)) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int total_time = 0;
    int completed[n]; // to track completed processes
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    float total_waiting_time = 0.0;
    float total_burst_time = 0.0;
    float total_turnaround_time = 0.0;

    printf("-------------------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Waiting Time | Turnaround Time   |\n");
    printf("-------------------------------------------------------------------------\n");

    int sequence[n]; // Array to store the sequence of processes
    int seq_index = 0; // Index to track the position in the sequence array

    for (int i = 0; i < n; i++) {
        int min_burst = -1;
        int selected_process = -1;
        for (int j = 0; j < n; j++) {
            if (completed[j] == 0 && processes[j].arrival_time <= total_time) {
                if (min_burst == -1 || processes[j].burst_time < min_burst) {
                    min_burst = processes[j].burst_time;
                    selected_process = j;
                }
            }
        }

        if (selected_process == -1) {
            // No process is available to run at this time
            total_time++;
            i--; // Try again in the next time unit
        } else {
            completed[selected_process] = 1;
            int waiting_time = total_time - processes[selected_process].arrival_time;
            int turnaround_time = waiting_time + processes[selected_process].burst_time;
            total_waiting_time += waiting_time;
            total_burst_time += processes[selected_process].burst_time;
            total_turnaround_time += turnaround_time;

            // Print process details
            printf("|    %2d   |      %2d      |     %3d    |      %3d      |        %3d       |\n",
                   processes[selected_process].process_id,
                   processes[selected_process].arrival_time,
                   processes[selected_process].burst_time,
                   waiting_time, turnaround_time);

            // Store the process in the sequence array
            sequence[seq_index++] = processes[selected_process].process_id;

            total_time += processes[selected_process].burst_time;
        }
    }

    printf("-------------------------------------------------------------------------\n");

    float avg_waiting_time = total_waiting_time / n;
    float avg_burst_time = total_burst_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Burst Time = %.2f\n", avg_burst_time);
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);

    // Print the sequence of processes
    printf("Sequence of processes: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", sequence[i]);
    }
    printf("\n");
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    sjfScheduling(processes, n);
    printf("Sahib Preet Singh AI-ML OO713211621\n");
    return 0;
}
