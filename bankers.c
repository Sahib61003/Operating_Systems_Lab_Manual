#include <stdio.h>

int main() {
    
    int num_processes, num_resources, i, j, k;
    num_processes = 5;
    num_resources = 3;
    int allocation[5][3] = { { 1, 0, 2 },
                             { 2, 1, 0 },
                             { 2, 0, 1 },
                             { 1, 2, 1 },
                             { 0, 1, 2 } };
 
    int max_demand[5][3] = { { 6, 4, 3 },
                             { 3, 2, 2 },
                             { 5, 1, 2 },
                             { 3, 3, 3 },
                             { 4, 3, 2 } };
 
    int available_resources[3] = { 3, 3, 2 };
 
    int finish[num_processes], safe_sequence[num_processes], ind = 0;
    for (k = 0; k < num_processes; k++) {
        finish[k] = 0;
    }
    int need[num_processes][num_resources];
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++)
            need[i][j] = max_demand[i][j] - allocation[i][j];
    }
    int y = 0;
    for (k = 0; k < num_processes; k++) {
        for (i = 0; i < num_processes; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > available_resources[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    safe_sequence[ind++] = i;
                    for (y = 0; y < num_resources; y++)
                        available_resources[y] += allocation[i][y];
                    finish[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    for(int i=0; i<num_processes; i++) {
        if(finish[i] == 0) {
            flag = 0;
            printf("The following system is not safe");
            break;
        }
    }

    if(flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < num_processes - 1; i++)
            printf(" P%d ->", safe_sequence[i]);
        printf(" P%d", safe_sequence[num_processes - 1]);
    }
    printf("\nSahib Preet Singh AI-ML 00713211621\n");
    return 0;
}
