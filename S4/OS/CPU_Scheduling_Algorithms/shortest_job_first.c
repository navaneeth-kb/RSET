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
    printf("Enter no of processes:");
    scanf("%d", &n);
    // Input process details
    for (int i = 0; i < n; i++) {
        printf("%d:Enter pid:", i);
        scanf("%d", &p[i].pid);
        printf("Enter arrival time:");
        scanf("%d", &p[i].arrivalTime);
        printf("Enter burst time:");
        scanf("%d", &p[i].burstTime);
    }

    // Sort processes based on priority
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (p[j].arrivalTime> p[j + 1].arrivalTime)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int currentTime=0;
    int completed=0;
    while(completed<n)
    {
        int minID=-1;
        for(int i=0;i<n;i++)
        {

            if (p[i].arrivalTime<=currentTime && p[i].completionTime==0)
            {
                if (p[i].burstTime<p[minID].burstTime || minID==-1)
                {
                    minID=i;
                }
            }
        }

        if(minID!=-1)
        {
            currentTime+=p[minID].burstTime;
            p[minID].completionTime=currentTime;
            completed++;
        }
        else
        {
            currentTime++;
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
