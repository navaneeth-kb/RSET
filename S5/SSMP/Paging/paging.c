#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct process
{
    int pid;
    int psize;
    int frames[20];
    int frames_allocated;
} p[100];

struct frame
{
    int avail;
    int frag;
};

int total_frames = 0;
int num_process = 0;
int avail_frames = 0;
int fsize;

void insertprocess(int pid, int psize, struct frame f[100], int frames_req)
{
    if (frames_req > avail_frames)
    {
        printf("Not enough frames available\n");
        return;
    }

    p[num_process].pid = pid;
    p[num_process].psize = psize;
    p[num_process].frames_allocated = 0;
    for (int i = 0; i < 20; i++)
    {
        p[num_process].frames[i] = -1; // Initialize frame allocation array
    }

    int j = 0;
    for (int i = 0; i < total_frames && j < frames_req; i++)
    {
        if (f[i].avail == -1) // Frame is available
        {
            f[i].avail = 1; // Mark frame as occupied
            p[num_process].frames[j] = i; // Allocate frame to process
            j++;
            p[num_process].frames_allocated++;
        }
    }

    avail_frames -= frames_req;
    num_process++;
    printf("Process allocated successfully.\n");
}

void deleteprocess(int pid, struct frame f[100])
{
    int i;
    for (i = 0; i < num_process; i++)
    {
        if (p[i].pid == pid)
        {
            break;
        }
    }

    if (i < num_process) // Process found
    {
        for (int j = 0; j < p[i].frames_allocated; j++)
        {
            int frame_idx = p[i].frames[j];
            f[frame_idx].avail = -1; // Free the frame
            avail_frames++;
        }

        printf("Process %d deleted successfully.\n", pid);

        // Shift remaining processes up to fill the gap
        for (int k = i; k < num_process - 1; k++)
        {
            p[k] = p[k + 1];
        }

        num_process--;
    }
    else
    {
        printf("Process with PID %d not found.\n", pid);
    }
}

void display(struct frame f[100])
{
    printf("PID\tFrames Allocated\n");
    printf("----------------------------\n");

    for (int i = 0; i < num_process; i++)
    {
        printf("%d\t", p[i].pid);
        for (int j = 0; j < p[i].frames_allocated; j++)
        {
            printf("%d ", p[i].frames[j]);
        }
        printf("\n");
    }

    int total_internal_frag = 0;
    for (int i = 0; i < num_process; i++)
    {
        int allocated_memory = p[i].frames_allocated * fsize;
        int internal_frag = allocated_memory - p[i].psize;
        total_internal_frag += internal_frag;
    }

    printf("\nTotal Internal Fragmentation: %d\n", total_internal_frag);
}

void main()
{
    int msize;
    printf("Enter the memory size: ");
    scanf("%d", &msize);
    printf("Enter the size of frame: ");
    scanf("%d", &fsize);
    total_frames = msize / fsize;

    struct frame f[100];
    for (int i = 0; i < total_frames; i++)
    {
        f[i].avail = -1; // Initialize all frames as free
        f[i].frag = fsize; // Initialize fragmentation size
    }

    avail_frames = total_frames;

    int ch, pid, psize;
    while (1)
    {
        printf("\n1. Create Process\t2. Delete Process\t3. Display Processes\t4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                printf("Enter Process ID: ");
                scanf("%d", &pid);
                printf("Enter Process Size: ");
                scanf("%d", &psize);
                int frames_req = ceil((float)psize / fsize); // Calculate required frames
                insertprocess(pid, psize, f, frames_req);
                break;

            case 2:
                printf("Enter PID of process to delete: ");
                scanf("%d", &pid);
                deleteprocess(pid, f);
                break;

            case 3:
                display(f);
                break;

            case 4:
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
