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
}File[10];

int n_blocks=0;
int n_file=0;

void main()
{
    int idx=0;
    char fname[50];
    int msize,bsize,avail_blocks,fblocks;
    printf("Enter memory size:");
    scanf("%d",&msize);
    printf("Enter block size:");
    scanf("%d",&bsize);
    n_blocks=msize/bsize;
    avail_blocks=n_blocks;
    printf("No of blocks:%d",n_blocks);

    struct blocks b[n_blocks];
    for(int i=0;i<n_blocks;i++)
    {
        b[i].avail=0;
        b[i].id=i;
    }

    while(1)
    {
        int ch;
        printf("\n\n1-ALLOCATE FILE\n2-SHOW ALLOCATION TABLE\n\n");
        printf("Enter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("Enter the name of file:");
                scanf("%s",fname);
                printf("Enter the no of blocks required:");
                scanf("%d",&fblocks);
                if(fblocks>avail_blocks)
                {
                    printf("Enough blocks not available");
                    break;
                }
                avail_blocks-=fblocks;
                int j=0;
                for(int i=0;i < n_blocks && j < fblocks;i++)
                {
                    if(b[i].avail==0)
                    {
                        b[i].avail=1;
                        File[n_file].block_ids[j]=b[i].id;
                        j++;
                    }
                }
                strcpy(File[n_file].name,fname);
                File[n_file].fsize=fblocks;
                n_file++;
                break;
            case 2:
                printf("\nAllocation Table");
                printf("\n");
                printf("\nFile name\t\tFile size\t\tBlocks allocated");
                for(int i=0;i<n_file;i++)
                {
                    printf("\n");
                    printf("%s\t%d\t",File[i].name,File[i].fsize);
                    for(int j=0;j<File[i].fsize;j++)
                    {
                        printf("%d ",File[i].block_ids[j]);
                    }
                }
                break;
        }
    }
}
