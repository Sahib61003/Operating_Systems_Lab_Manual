#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("_________________________________________________________\n\n");
    printf("| Process | Burst Time | Waiting Time | Turnaround Time |\n");
    printf("_________________________________________________________\n\n");
    
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("|    %2d   |     %3d     |      %3d     |        %3d     |\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("_________________________________________________________\n");

    float s = (float)total_wt / (float)n;
    float t = (float)total_tat / (float)n;
    printf("Average waiting time = %f\n", s);
    printf("Average turnaround time = %f\n", t);
}

int main() {
    int processes[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {7, 3, 10, 9, 6, 12};
    findavgTime(processes, n, burst_time);
    printf("Sahib Preet Singh AI-ML OO713211621");
    return 0;
}

 