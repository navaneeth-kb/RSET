#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
    char process_id[5];
    int process_size;
    int frames[100];  // Arbitrarily large for this example
    int num_frames;
    int internal_frag;
};

struct process* processes;
int total_processes = 0;
int* free_frames;
int total_free_frames;
int MEMORY_SIZE;  
int FRAME_SIZE;    

void initialize_free_frames() {
    for (int i = 0; i < total_free_frames; i++) {
        free_frames[i] = 1;  
    }
}

void create_process() {
    if (total_free_frames == 0) {
        printf("No free frames available\n");
        return;
    }

    struct process new_process;
    printf("Enter process ID: ");
    scanf("%s", new_process.process_id);
    printf("Enter process size (in KB): ");
    scanf("%d", &new_process.process_size);

    new_process.num_frames = (new_process.process_size + FRAME_SIZE - 1) / FRAME_SIZE;
    new_process.internal_frag = (new_process.num_frames * FRAME_SIZE) - new_process.process_size;

    if (new_process.num_frames > total_free_frames) {
        printf("Not enough free frames available\n");
        return;
    }

    int frame_index = 0;
    for (int i = 0; i < total_free_frames && frame_index < new_process.num_frames; i++) {
        if (free_frames[i]) {
            new_process.frames[frame_index++] = i;
            free_frames[i] = 0; 
        }
    }

    total_free_frames -= new_process.num_frames;
    processes[total_processes++] = new_process;
    printf("Process %s created successfully\n", new_process.process_id);
}

void delete_process() {
    char process_id[5];
    printf("Enter process ID to delete: ");
    scanf("%s", process_id);

    int found = 0;
    for (int i = 0; i < total_processes; i++) {
        if (strcmp(processes[i].process_id, process_id) == 0) {
            found = 1;
            for (int j = 0; j < processes[i].num_frames; j++) {
                free_frames[processes[i].frames[j]] = 1;  
            }
            total_free_frames += processes[i].num_frames;

            for (int k = i; k < total_processes - 1; k++) {
                processes[k] = processes[k + 1];
            }
            total_processes--;
            printf("Process %s deleted successfully.\n", process_id);
            break;
        }
    }

    if (!found) {
        printf("Process %s not found.\n", process_id);
    }
}

void display_processes() {
    int total_occupied_frames = 0;

    printf("Process   Frames Occupied   Frames   Internal Fragmentation\n");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < total_processes; i++) {
        printf("%s\t   %d\t\t    ", processes[i].process_id, processes[i].num_frames);
        for (int j = 0; j < processes[i].num_frames; j++) {
            printf("%d ", processes[i].frames[j]);
        }
        printf("\t\t%d KB\n", processes[i].internal_frag);
        total_occupied_frames += processes[i].num_frames;
    }

    int total_frag = 0;
    for (int i = 0; i < total_processes; i++) {
        total_frag += processes[i].internal_frag;
    }

    printf("\nTotal Internal Fragmentation: %dKB\n", total_frag);
    printf("Total Frames Occupied: %d\n", total_occupied_frames);
}

int main() {
    printf("Enter total memory size (in KB): ");
    scanf("%d", &MEMORY_SIZE);
    printf("Enter frame size (in KB): ");
    scanf("%d", &FRAME_SIZE);

    total_free_frames = MEMORY_SIZE / FRAME_SIZE;
    free_frames = (int*)malloc(total_free_frames * sizeof(int));
    processes = (struct process*)malloc(total_free_frames * sizeof(struct process));

    initialize_free_frames();

    int choice;
    while (1) {
        printf("\nMENU\n");
        printf("1. Create Process\n");
        printf("2. Delete Process\n");
        printf("3. Display Processes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_process();
                break;
            case 2:
                delete_process();
                break;
            case 3:
                display_processes();
                break;
            case 4:
                free(free_frames);
                free(processes);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
