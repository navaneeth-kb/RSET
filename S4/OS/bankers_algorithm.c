#include <stdio.h>
#include <stdbool.h>

void calculateNeed(int P, int R, int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) 
    {
        for (int j = 0; j < R; j++) 
        {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

bool isSafe(int P, int R, int processes[], int avail[], int max[P][R], int allot[P][R]) {
    int need[P][R];
    calculateNeed(P, R, need, max, allot);

    bool finish[P];
    for (int i = 0; i < P; i++) 
    {
        finish[i] = false;
    }

    int safeSeq[P];
    int work[R];
    for (int i = 0; i < R; i++) 
    {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) 
    {
        bool found = false;
        for (int i = 0; i < P; i++) 
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < R; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        break;
                    }
                }
                if (j == R) 
                {
                    for (int k = 0; k < R; k++) 
                    {
                        work[k] += allot[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) 
        {
            printf("System not in safe state\n");
            return false;
        }
    }
    printf("System in safe state\nSafe sequence is: ");
    for (int i = 0; i < P; i++) 
    {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

void main() 
{
    int P, R;
    printf("Enter the number of processes: ");
    scanf("%d", &P);
    int processes[P]; 
    
    printf("Enter the number of resources: ");
    scanf("%d", &R);
    int avail[R];
    
    for (int i = 0; i < P; i++) 
    {
        processes[i] = i;
    }

    printf("Enter the available resources (%d resource types): ", R);
    for (int i = 0; i < R; i++) 
    {
        scanf("%d", &avail[i]);
    }

    int max[P][R];
    printf("Enter the max resource matrix (%d processes and %d resources):\n", P, R);
    for (int i = 0; i < P; i++) 
    {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) 
        {
            scanf("%d", &max[i][j]);
        }
    }

    int allot[P][R];
    printf("Enter the allocation matrix (%d processes and %d resources):\n", P, R);
    for (int i = 0; i < P; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) 
        {
            scanf("%d", &allot[i][j]);
        }
    }

    if (isSafe(P, R, processes, avail, max, allot)) 
    {
        printf("The system can allocate resources safely\n");
    } 
    else 
    {
        printf("The system cannot allocate resources safely\n");
    }
}
