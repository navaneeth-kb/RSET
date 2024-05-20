#include<stdio.h>
#include<stdlib.h>

void simulateFIFO(int pages[],int n,int frames)
{
    int frame[frames],pageFault=0,found=0,front=0;
    for(int i=0;i<frames;i++)
    {
        frame[i]=-1;
    }
    printf("Reference Strings\tFrames\n");
    for(int i=0;i<n;i++)
    {
        found=0;
        for(int j=0;j<frames;j++)
        {
            if(frame[j]==pages[i])
            {
                found=1;
                break;
            }
        }
        if(found==0)
        {
            frame[front]=pages[i];
            front=(front+1)%frames;
            pageFault++;
        }
        printf("%d\t\t\t",pages[i]);
        for(int j=0;j<frames;j++)
        {
            if(frame[j]==-1)
            {
                printf(" \t");
            }
            else
            {
                printf("%d\t",frame[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults:%d\n",pageFault);
}
void simulateLRU(int pages[],int n,int frames)
{
    int frame[frames],counter[frames],time=0,pageFaults=0;
    for(int i=0;i<frames;i++)
    {
        frame[i]=-1;
        counter[i]=-1;
    }
    printf("Reference Strings\tFrames\n)");
    for(int i=0;i<n;i++)
    {
        int found=0,min=0;
        for(int j=0;j<frames;j++)
        {
            if(frame[j]==pages[i])
            {
                found=1;
                counter[j]=time++;
                break;
            }
        }
        if (found==0)
        {
            for(int j=0;j<frames;j++)
            {
                if(frame[j]==-1)
                {
                    min=j;
                    break;
                }
                else if(counter[j]<counter[min])
                {
                    min=j;
                }
            }
            frame[min]=pages[i];
            counter[min]=time++;
            pageFaults++;
        }
        printf("%d\t\t\t",pages[i]);
        for(int j=0;j<frames;j++)
        {
            if(frame[j]==-1)
            {
                printf(" ");
            }
            else
            {
                printf("%d\t",frame[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults:%d\n",pageFaults);
}

void main()
{
    int n, frame;
    int refString[100];
    printf("Enter length of reference string: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &refString[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &frame);
    printf("FIFO\n");
    simulateFIFO(refString, n, frame);
    printf("LRU\n");
    simulateLRU(refString, n, frame);
}
