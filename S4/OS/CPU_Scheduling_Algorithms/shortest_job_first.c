#include<stdio.h>
#include<stdlib.h>

struct process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int completion_time;
    int turnaround_time;
} p[10], temp;

void main() 
{
    int n, i, j, min_idx;
    float avg_waiting_time = 0.0f, avg_turnaround_time = 0.0f;

    printf("Enter the number of processes:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        printf("Enter the process ID:");
        scanf("%d", &p[i].id);
        printf("Enter the arrival time of process %d:", i);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time of process %d:", i);
        scanf("%d", &p[i].burst_time);
        printf("\n");
    }

    for (int i = 0; i < n - 1; i++) 
    {
        min_idx = i;
        for (int j = i + 1; j < n; j++) 
	{
            if (p[j].arrival_time < p[min_idx].arrival_time) 
	    {
                min_idx = j;
            }
        }
        if (min_idx != i) 
	{
            temp = p[i];
            p[i] = p[min_idx];
            p[min_idx] = temp;
        }
    }

    int previous_completion_time = p[0].arrival_time; // Initialize previous completion time
    for (int i = 0; i < n; i++) 
    {
        int smallest_burst_time = p[i].burst_time;
        int shortest_PRC = i;
        for (int j = i; j < n; j++) 
	{
            if (p[j].arrival_time <= previous_completion_time && p[j].burst_time < smallest_burst_time) 
	    {
                smallest_burst_time = p[j].burst_time;
                shortest_PRC = j;
            }
        }
        p[shortest_PRC].completion_time = previous_completion_time + p[shortest_PRC].burst_time;
        p[shortest_PRC].turnaround_time = p[shortest_PRC].completion_time - p[shortest_PRC].arrival_time;
        p[shortest_PRC].waiting_time = p[shortest_PRC].turnaround_time - p[shortest_PRC].burst_time;

        // Update previous completion time
        previous_completion_time = p[shortest_PRC].completion_time;

        // Swap processes
        temp = p[shortest_PRC];
        p[shortest_PRC] = p[i];
        p[i] = temp;

        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("Process ID \t Arrival Time \t Burst Time \t Waiting Time \t Completion Time \t Turnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t %d\t\t\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].completion_time, p[i].turnaround_time);
    }
    printf("\nAverage waiting time: %.2f\n", avg_waiting_time);
    printf("Average turn-around time: %.2f\n", avg_turnaround_time);
}
