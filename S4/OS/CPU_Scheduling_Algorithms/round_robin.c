#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

// Process structure
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

int main() {
    struct Process p[MAX_PROCESSES];
    int n, quantum;

    // Prompt user for number of p
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    //reading processes
    for(int i=0; i<n; i++) {
        printf("Enter the ID of process%d: ", i);
        scanf("%d", &p[i].pid);
        printf("Enter the Arrival Time of process%d: ", i);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the Burst Time of process%d: ", i);
        scanf("%d", &p[i].burst_time);
        printf("\n");
        p[i].remaining_burst_time = p[i].burst_time;
    }

    // Prompt user for quantum time
    printf("Enter quantum time: ");
    scanf("%d", &quantum);

    // Bubble sort processes based on arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Round Robin scheduling algorithm
    int remaining_processes = n;
    int current_time = 0;

    while (remaining_processes > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining_burst_time > 0)
            {
                int execute_time;
                if(p[i].remaining_burst_time < quantum)
                {
                    execute_time=p[i].remaining_burst_time;
                }
                else
                {
                    execute_time=quantum;
                }
                current_time += execute_time;
                p[i].remaining_burst_time -= execute_time;

                if (p[i].remaining_burst_time == 0)
                {
                    p[i].completion_time = current_time;
                    p[i].turnaround_time = current_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                    remaining_processes--;
                }
            }
        }
    }

    // Print process details
    printf("\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time,
               p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    // Calculate average waiting time
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += p[i].waiting_time;
    }
    float avg_waiting_time = total_waiting_time / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);

    // Calculate average turnaround time
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_turnaround_time += p[i].turnaround_time;
    }
    float avg_turnaround_time = total_turnaround_time / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
