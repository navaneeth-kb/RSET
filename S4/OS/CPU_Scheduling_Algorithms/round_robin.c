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

// Function prototypes
void bubble_sort(struct Process processes[], int n);
void round_robin(struct Process processes[], int n, int quantum);
float find_avg(struct Process processes[], int n);
float find_avgt(struct Process processes[], int n);

int main()
{
    struct Process processes[MAX_PROCESSES];
    int n, quantum;

    // Prompt user for number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    //reading processes
    int i;
	for(i=0; i<n; i++) 
    {
		printf("Enter the ID of process%d: ", i);
		scanf("%d", &processes[i].pid);
		printf("Enter the Arrival Time of process%d: ", i);
		scanf("%d", &processes[i].arrival_time);
		printf("Enter the Burst Time of process%d: ", i);
		scanf("%d", &processes[i].burst_time);
		printf("\n");
		processes[i].remaining_burst_time = processes[i].burst_time;
	}

    // Prompt user for quantum time
    printf("Enter quantum time: ");
    scanf("%d", &quantum);

    // Sort processes based on arrival time
    bubble_sort(processes, n);

    // Apply Round Robin scheduling algorithm
    round_robin(processes, n, quantum);

    // Print process details
    printf("\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Calculate average waiting time
    float avg_waiting_time = find_avg(processes, n);
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    
    // Calculate average turnaround time
    float avg_turnaround_time = find_avgt(processes, n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    

    return 0;
}

// Bubble sort function to sort processes based on arrival time
void bubble_sort(struct Process processes[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) 
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Round Robin scheduling algorithm
void round_robin(struct Process processes[], int n, int quantum) {
    int remaining_processes = n;
    int current_time = 0;

    while (remaining_processes > 0) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (processes[i].remaining_burst_time > 0) 
            {
                int execute_time = (processes[i].remaining_burst_time < quantum) ? processes[i].remaining_burst_time : quantum;
                current_time += execute_time;
                processes[i].remaining_burst_time -= execute_time;

                if (processes[i].remaining_burst_time == 0) 
                {
                    processes[i].completion_time = current_time;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    remaining_processes--;
                }
            }
        }
    }
}

// Function to find average waiting time
float find_avg(struct Process processes[], int n) {
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return total_waiting_time / n;
}

// Function to find average turnaround time
float find_avgt(struct Process processes[], int n) {
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
    }
    return total_turnaround_time / n;
}