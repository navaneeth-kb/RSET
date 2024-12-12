#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct blocks
{
    int avail;
    int id;
};

struct files
{
    char name[50];
    int block_ids[50];
    int fsize;
} File[10];

int n_blocks = 0;
int n_file = 0;
int avail_blocks;

void main()
{
    char fname[50];
    int msize, bsize, fblocks;
    printf("Enter memory size: ");
    scanf("%d", &msize);
    printf("Enter block size: ");
    scanf("%d", &bsize);

    n_blocks = msize / bsize;
    avail_blocks = n_blocks;
    printf("Number of blocks: %d\n", n_blocks);

    struct blocks b[n_blocks];
    for(int i = 0; i < n_blocks; i++)
    {
        b[i].avail = 0;
        b[i].id = i;
    }

    while(1)
    {
        int idx=0;
        int ch;
        printf("\n1-ALLOCATE FILE\n2-SHOW ALLOCATION TABLE\n3-EXIT\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                printf("Enter the name of the file: ");
                scanf("%s", fname);
                printf("Enter the number of blocks required: ");
                scanf("%d", &fblocks);
                if(fblocks > avail_blocks)
                {
                    printf("Not enough blocks available\n");
                    break;
                }

                int j=0;
                avail_blocks -= fblocks;
                for(int i=0;i<fblocks;i++)
                {
                    while(b[idx].avail==1)
                    {
                        idx=rand()%n_blocks;
                    }
                    if(b[idx].avail==0)
                    {
                        b[idx].avail=1;
                        File[n_file].block_ids[j]=b[idx].id;
                        j++;
                    }
                }
                strcpy(File[n_file].name, fname);
                File[n_file].fsize = fblocks;
                n_file++;
                break;

            case 2:
                printf("\nAllocation Table\n");
                printf("File Name\tFile Size\tBlocks Allocated\n");
                for(int i = 0; i < n_file; i++)
                {
                    printf("%s\t\t%d\t\t", File[i].name, File[i].fsize);
                    for(int j = 0; j < File[i].fsize; j++)
                    {
                        printf("%d ", File[i].block_ids[j]);
                    }
                    printf("\n");
                }
                break;

            case 3:
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
