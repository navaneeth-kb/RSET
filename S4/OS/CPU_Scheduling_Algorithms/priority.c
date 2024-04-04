#include<stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turn_aroundtime;
    int completionTime;
    int priority;
};

struct Process processes[10];

void sort(int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void findWaitingTime(int n) {
    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = processes[i].turn_aroundtime - processes[i].burstTime;
    }
}

void findTurnAroundTime(int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turn_aroundtime = processes[i].completionTime - processes[i].arrivalTime;
    }
}

void findCompletionTime(int n) {
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    for (int i = 1; i < n; i++) {
        int currentTime = processes[i - 1].completionTime;
        if (processes[i].arrivalTime < currentTime) {
            processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
        } else {
            processes[i].completionTime = processes[i].arrivalTime + processes[i].burstTime;
        }
    }
}

void findAvg(int n) {
    int total_wt = 0, total_tt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].waitingTime;
        total_tt += processes[i].turn_aroundtime;
    }
    printf("\nAverage wait time = %f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %f", (float)total_tt / (float)n);
}

int main() {
    int n;
    printf("Enter no of processes:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("%d:Enter pid:", i);
        scanf("%d", &processes[i].pid);
        printf("\nEnter arrival time:");
        scanf("%d", &processes[i].arrivalTime);
        printf("\nEnter burst time:");
        scanf("%d", &processes[i].burstTime);
        printf("\nEnter priority:");
        scanf("%d", &processes[i].priority);
    }

    sort(n);
    findCompletionTime(n);
    findTurnAroundTime(n);
    findWaitingTime(n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t%d\t%d", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].turn_aroundtime, processes[i].waitingTime);
    }

    findAvg(n);
    printf("\n");
    return 0;
}