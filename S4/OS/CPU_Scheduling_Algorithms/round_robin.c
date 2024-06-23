#include <stdio.h>

struct Process {
    int pid;   // Process ID
    int arrivalTime; // Arrival Time
    int burstTime;   // Burst Time
    int completionTime; // Completion Time
    int turnaroundTime; // Turnaround Time
    int waitingTime; // Waiting Time
    int remainingTime; // Remaining Time
} processes[10];

int numberOfProcesses;
int timeQuantum;
struct Process readyQueue[30];
int front = 0, rear = 0;
int currentIndex = 1;
struct Process completedProcesses[30];
int completedCount = 0;

void sortProcessesByArrivalTime() 
{
    //bubble sort
    struct Process temp;
    for (int i = 0; i < numberOfProcesses; i++) 
    {
        for (int j = 0; j < numberOfProcesses - 1 - i; j++) 
        {
            if (processes[j + 1].arrivalTime < processes[j].arrivalTime) 
            {
                temp = processes[j + 1];
                processes[j + 1] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void roundRobinScheduling() {
    int currentTime = 0;
    int remainingProcesses = numberOfProcesses;
    readyQueue[front] = processes[0];
    rear++;

    while (front != rear) {
        int executionTime;
        if (readyQueue[front].remainingTime > timeQuantum) 
        {
            executionTime = timeQuantum;
        } 
        else 
        {
            executionTime = readyQueue[front].remainingTime;
        }
        currentTime += executionTime;
        readyQueue[front].remainingTime -= executionTime;

        int oldIndex = currentIndex;
        while (currentIndex < numberOfProcesses && processes[currentIndex].arrivalTime <= currentTime) 
        {
            currentIndex++;
        }

        if (oldIndex != currentIndex) 
        {
            for (int i = oldIndex; i < currentIndex; i++) 
            {
                readyQueue[rear] = processes[i];
                rear++;
            }
        }

        if (readyQueue[front].remainingTime == 0) 
        {
            readyQueue[front].completionTime = currentTime;
            completedProcesses[completedCount] = readyQueue[front];
            completedCount++;
            front++;
        } 
        else 
        {
            readyQueue[rear] = readyQueue[front];
            rear++;
            front++;
        }
    }
}

void main() 
{
    printf("Enter the number of processes: ");
    scanf("%d", &numberOfProcesses);
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < numberOfProcesses; i++) 
    {
        printf("Enter the PID, arrival time, and burst time of process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].pid, &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    sortProcessesByArrivalTime();
    roundRobinScheduling();

    printf("PID\tArrival Time\tBurst Time\tCompletion Time\n");
    for (int i = 0; i < numberOfProcesses; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\n", completedProcesses[i].pid, completedProcesses[i].arrivalTime, completedProcesses[i].burstTime, completedProcesses[i].completionTime);
    }
}
