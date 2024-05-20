#include<stdio.h>
#include<stdlib.h>

struct block
{
    struct block *prev;
    int block_no;
    int block_size;
    int process_no;
    int free_space;
    struct block *next;
};
struct process
{
    int process_no;
    int status;
    int process_size;
};

void first_fit(struct block *start,struct process processes[],int no_of_processes)
{
    struct block *ptr;
    for(int i=0;i<no_of_processes;i++)
    {
        for(ptr=start;ptr!=NULL;ptr=ptr->next)
        {
            if (ptr->process_no==-1 && ptr->block_size>=processes[i].process_size)
            {
                processes[i].status=ptr->block_no;
                ptr->process_no=processes[i].process_no;
                ptr->free_space-=processes[i].process_size;
                break;
            }
        }
    }
}

void best_fit(struct block *start,struct process processes[],int no_of_processes)
{
    struct block *ptr,*smallest;
    int smallest_size;
    for(int i=0;i<no_of_processes;i++)
    {
        smallest=NULL;
        smallest_size=100000000000;
        for(ptr=start;ptr!=NULL;ptr=ptr->next)
        {
            if(ptr->process_no==-1 && ptr->block_size>=processes[i].process_size && ptr->block_size<smallest_size)
            {
                smallest=ptr;
                smallest_size=ptr->block_size;
            }
        }
        if(smallest!=NULL)
        {
            processes[i].status=smallest->block_no;
            smallest->process_no=processes[i].process_no;
            smallest->free_space-=processes[i].process_size;
        }
    }
}

void worst_fit(struct block *start,struct process processes[],int no_of_processes)
{
    struct block *ptr,*largest;
    int largest_size;
    for(int i=0;i<no_of_processes;i++)
    {
        largest=NULL;
        largest_size=0;
        for(ptr=start;ptr!=NULL;ptr=ptr->next)
        {
            if(ptr->process_no==-1 && ptr->block_size>=processes[i].process_size && ptr->block_size>largest_size)
            {
                largest=ptr;
                largest_size=ptr->block_size;
            }
        }
        if(largest!=NULL)
        {
            processes[i].status=largest->block_no;
            largest->process_no=processes[i].process_no;
            largest->free_space-=processes[i].process_size;
        }
    }
}

void display(struct block *start,struct process processes[],int no_of_processes)
{
    struct block *ptr;
    printf("\nBlock details:");
    printf("\nBlock No\tBlock size\tFree space\tProcess No");
    for(ptr=start;ptr!=NULL;ptr=ptr->next)
    {
        printf("\n%d\t\t%d\t\t%d\t\t",ptr->block_no,ptr->block_size,ptr->free_space);
        if(ptr->process_no==-1)
        {
            printf("-");
        }
        else
        {
            printf("%d",ptr->process_no);
        }
    }

    printf("\nProcess details");
    printf("\nProcess No\tProcess size\tProcess status");
    for(int i=0;i<no_of_processes;i++)
    {
        printf("\n%d\t\t%d\t\t",processes[i].process_no,processes[i].process_size);
        if(processes[i].status>=1)
        {
            printf("%d",processes[i].status);
        }
        else
        {
            printf("Unallocated");
        }
    }
}

void reset_allocations(struct block *start,struct process processes[],int no_of_processes)
{
    struct block *ptr;
    for(ptr=start;ptr!=NULL;ptr=ptr->next)
    {
        ptr->process_no=-1;
        ptr->free_space=ptr->block_size;
    }
    for(int i=0;i<no_of_processes;i++)
    {
        processes[i].status=-1;
    }
}

void main()
{
    struct block *start=NULL,*end=NULL,*new_block=NULL,*ptr=NULL;
    struct process processes[10];
    int no_of_processes,no_of_blocks;

    printf("Enter the number of blocks:");
    scanf("%d",&no_of_blocks);

    for(int i=0;i<no_of_blocks;i++)
    {
        new_block=(struct block*)malloc(sizeof(struct block));
        new_block->prev=new_block->next=NULL;
        new_block->block_no=i+1;
        new_block->process_no=-1;
        printf("Enter the size of block:");
        scanf("%d",&new_block->block_size);
        new_block->free_space=new_block->block_size;
        if (start==NULL && end==NULL)
        {
            start=end=new_block;
        }
        else
        {
            end->next=new_block;
            new_block->prev=end;
            end=new_block;
        }
    }

    printf("Enter the number of processes:");
    scanf("%d",&no_of_processes);
    for(int i=0;i<no_of_processes;i++)
    {
        printf("Enter the process size:");
        scanf("%d",&processes[i].process_size);
        processes[i].process_no=i+1;
    }

    // First fit allocation
    printf("\nFirst fit allocation:\n");
    first_fit(start, processes, no_of_processes);
    display(start, processes, no_of_processes);

    // Clear allocations
    reset_allocations(start, processes, no_of_processes);

    // Best fit allocation
    printf("\n\nBest fit allocation:\n");
    best_fit(start, processes, no_of_processes);
    display(start, processes, no_of_processes);

    // Clear allocations
    reset_allocations(start, processes, no_of_processes);

    // Worst fit allocation
    printf("\n\nWorst fit allocation:\n");
    worst_fit(start, processes, no_of_processes);
    display(start, processes, no_of_processes);
}
