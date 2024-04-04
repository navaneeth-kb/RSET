#include <stdio.h>
#include <stdlib.h>
int a[50],max,rear=-1,front=-1;
void enqueue(int value)
{
    if((rear+1)%max==front)
    {
        printf("full");
    }
    else if(rear==-1)
    {
        front=0;
        rear=0;
        a[rear]=value;
    }
    else
    {
        rear=(rear+1)%max;
        a[rear]=value;
    }
}
void dequeue()
{
    if (rear==-1)
    {
        printf("empty");
    }
    else if(front==rear)
    {
        printf("deleted element is %d",a[front]);
        front=-1;
        rear=-1;
    }
    else
    {
        printf("deleted element is %d",a[front]);
        front=(front+1)%max;
    }
}
void display()
{
    if (rear==-1)
    {
        printf("empty");
    }
    else
    {
        for(int i=front;i<=rear;i++)
        {
            printf("%d\t",a[i]);
        }
    }
}
void main()
{
    int ch,val;
    printf("Enter max value:");
    scanf("%d",&max);
    while(1)
    {
        printf("\n1-PUSH \n2-POP \n3-DISPLAY \n4-EXIT");
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\nInput value:");
                    scanf("%d",&val);
                    enqueue(val);
                    break;
            case 2: dequeue();
                    break;
            case 3: display();
                    break;
            case 4: exit(0);
                    break;
            default: printf("invalid choice");
                     break;
        }
    }
}
