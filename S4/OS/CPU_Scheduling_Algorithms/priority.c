#include<stdio.h>

struct Process 
{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turn_aroundtime;
    int completionTime;
    int priority;
} p[10];

void main() 
{
    int n;
    printf("Enter no of p:");
    scanf("%d", &n);
    // Input process details
    for (int i = 0; i < n; i++) {
        printf("%d:Enter pid:", i);
        scanf("%d", &p[i].pid);
        printf("\nEnter arrival time:");
        scanf("%d", &p[i].arrivalTime);
        printf("\nEnter burst time:");
        scanf("%d", &p[i].burstTime);
        printf("\nEnter priority:");
        scanf("%d", &p[i].priority);
    }

    // Sort processes based on priority
    struct Process temp;
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - 1 - i; j++) 
        {
            if (p[j].priority > p[j + 1].priority) 
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Find completion time
    p[0].completionTime = p[0].arrivalTime + p[0].burstTime;
    for (int i = 1; i < n; i++) 
    {
        int currentTime = p[i - 1].completionTime;
        if (p[i].arrivalTime < currentTime) 
        {
            p[i].completionTime = p[i - 1].completionTime + p[i].burstTime;
        } 
        else 
        {
            p[i].completionTime = p[i].arrivalTime + p[i].burstTime;
        }
    }

    // Find turnaround time and waiting time
    int total_wt = 0, total_tt = 0;
    for (int i = 0; i < n; i++) 
    {
        p[i].turn_aroundtime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turn_aroundtime - p[i].burstTime;
        total_wt += p[i].waitingTime;
        total_tt += p[i].turn_aroundtime;
    }

    // Print process details
    printf("PID\tAT\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; i++) 
    {
        printf("\n%d\t%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turn_aroundtime, p[i].waitingTime);
    }

    // Print averages
    printf("\nAverage wait time = %f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %f", (float)total_tt / (float)n);

    printf("\n");
}
