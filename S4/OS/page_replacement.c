#include <stdio.h>

void simulateFIFO(int pages[], int n, int frames) {
    int frame[frames], front = 0, pageFaults = 0;
    for (int i = 0; i < frames; i++) 
        frame[i] = -1;

    printf("Reference String\tFrames\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            pageFaults++;
        }
        printf("%d\t\t\t", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) 
                printf("%d ", frame[j]);
            else 
                printf("  ");
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

void simulateLRU(int pages[], int n, int frames) {
    int frame[frames], counter[frames], time = 0, pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    printf("Reference String\tFrames\n");
    for (int i = 0; i < n; i++) {
        int found = 0, min = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                counter[j] = time++;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    min = j;
                    break;
                } else if (counter[j] < counter[min]) {
                      min = j;
                }
            }
            frame[min] = pages[i];
            counter[min] = time++;
            pageFaults++;
        }
        printf("%d\t\t\t", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("  ");
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, frame;
    int refString[100];
    printf("Enter length of reference string: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &refString[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &frame);

    int choice;

    printf("Choose Page Replacement Algorithm:\n");
    printf("1. FIFO (First-In, First-Out)\n");
    printf("2. LRU (Least Recently Used)\n");
    do{
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            simulateFIFO(refString, n, frame);
            break;
        case 2:
            simulateLRU(refString, n, frame);
            break;
        case 3:exit(0);
        default:
            printf("Invalid choice!\n");
    }
    }while(choice!=3);
    return 0;
}
