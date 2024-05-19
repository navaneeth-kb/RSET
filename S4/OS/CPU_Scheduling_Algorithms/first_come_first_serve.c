#include<stdio.h>
#include<stdlib.h>

struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int completion_time;
    int turnaround_time;
}p[10],temp;

void main()
{
    int n,i,j,min_idx;
    float avg_waiting_time=0.0f,avg_turnaround_time=0.0f;

    printf("Enter the number of processes:");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Enter the process ID:");
        scanf("%d",&p[i].id);
        printf("Enter the arrival time of process %d:",i);
        scanf("%d",&p[i].arrival_time);
        printf("Enter the burst time of process %d:",i);
        scanf("%d",&p[i].burst_time);
        printf("\n");
    }

    for(int i=0;i<n-1;i++)
    {
        min_idx=i;
        for(j=i+1;j<n;j++)
        {
            if(p[j].arrival_time<p[min_idx].arrival_time)
            {
                min_idx=j;
            }
        }
        if(min_idx!=i)
        {
            temp=p[i];
            p[i]=p[min_idx];
            p[min_idx]=temp;
        }
    }

    p[0].waiting_time=0;
    p[0].completion_time=p[0].arrival_time+p[0].burst_time;
    p[0].turnaround_time=p[0].burst_time;
    avg_turnaround_time=avg_turnaround_time+p[0].turnaround_time;

    for(int i=1;i<n;i++)
    {
        p[i].waiting_time=p[i-1].completion_time-p[i].arrival_time;
        if(p[i].waiting_time<0)
        {
            p[i].waiting_time=0;
        }
        p[i].completion_time=p[i].arrival_time+p[i].burst_time+p[i].waiting_time;
        p[i].turnaround_time=p[i].burst_time+p[i].waiting_time;
        avg_waiting_time=avg_waiting_time+p[i].waiting_time;
        avg_turnaround_time=avg_turnaround_time+p[i].turnaround_time;
    }
    avg_waiting_time/=n;
    avg_turnaround_time/=n;

    printf("Process ID \t Arrival Time \t Burst Time \t Waiting Time \t Completion Time \t Turnaround Time\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t %d\t\t\n",p[i].id,p[i].arrival_time,p[i].burst_time, p[i].waiting_time, p[i].completion_time, p[i].turnaround_time);
    }
    printf("\nAverage waiting time: %.2f\n", avg_waiting_time);
    printf("Average turn-around time: %.2f\n", avg_turnaround_time);

}
