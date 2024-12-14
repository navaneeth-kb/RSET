#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct process
{
    int pid;
    int psize;
    int frames[30];
    int frames_allocated;
    int int_frag;
}p[100];

struct frame
{
    int avail;
}f[100];

int fsize;
int total_frames;
int avail_frames;
int num_process;

void insertprocess(int pid,int psize,int process_frames,int process_frag)
{
    if(process_frames>avail_frames)
    {
        printf("Not enough frames available for process");
        return;
    }

    int j=0;
    p[num_process].pid=pid;
    p[num_process].psize=psize;
    p[num_process].int_frag=process_frag;
    p[num_process].frames_allocated=process_frames;
    for (int i=0; i<total_frames && j<process_frames;i++)
    {
        if(f[i].avail==-1)
        {
            f[i].avail=1;
            p[num_process].frames[j]=i;
            j++;
        }
    }

    avail_frames -= process_frames;
    num_process++;
    printf("Process allocated successfully\n");
}

void deleteprocess(int pid)
{
    int i;
    for (i=0;i<num_process;i++)
    {
        if(p[i].pid==pid)
        {
            break;
        }
    }

    if(i<num_process)
    {
        for(int j=0;j<p[i].frames_allocated;j++)
        {
            int frame_idx = p[i].frames[j];
            f[frame_idx].avail=-1;
        }
        avail_frames+=p[i].frames_allocated;

        for(int k=i;k<num_process;k++)
        {
            p[k]=p[k+1];
        }
        num_process--;
        printf("Process deleted");
    }
    else
    {
        printf("Process with PID %d not found.\n", pid);
    }
}

void display()
{
    printf("\nPROCESS ID\tFRAMES OCCUPIED\tFRAMES\tINTERNAL FRAGMENTATION\n");
    int total_internal_frag = 0;

    for (int i = 0; i < num_process; i++)
    {
        printf("%d\t\t", p[i].pid);
        printf("%d\t\t", p[i].frames_allocated);
        for (int j = 0; j < p[i].frames_allocated; j++)
        {
            printf("%d ", p[i].frames[j]);
        }
        printf("\t\t");
        printf("%d\t\t", p[i].int_frag);
        total_internal_frag+=p[i].int_frag;
        printf("\n");
    }
    printf("\nTotal Internal Fragmentation: %d\n", total_internal_frag);
}

void main()
{
    int psize,msize;
    printf("Enter total memory size:");
    scanf("%d",&msize);
    printf("Enter frame size:");
    scanf("%d",&fsize);
    total_frames=msize/fsize;
    printf("No. of frames available:%d",total_frames);

    for (int i=0;i<100;i++)
    {
        f[i].avail=-1;
    }
    avail_frames=total_frames;

    while(1)
    {
        int ch,pid,psize,frag;
        printf("\n\n1-CREATE PROCESS\n2-DELETE PROCESS\n3-DISPLAY PROCESS\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                printf("Enter Process ID: ");
                scanf("%d", &pid);
                printf("Enter Process Size: ");
                scanf("%d", &psize);
                int p_frames=ceil((float)psize/fsize);
                int frame_allocated_memory=p_frames*fsize;
                int frag=frame_allocated_memory-psize;
                insertprocess(pid,psize,p_frames,frag);
                break;

            case 2:
                printf("Enter PID of process to delete: ");
                scanf("%d", &pid);
                deleteprocess(pid);
                break;

            case 3:
                display();
                break;
        }
    }
}
