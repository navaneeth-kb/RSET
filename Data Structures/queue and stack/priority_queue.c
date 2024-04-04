#include <stdio.h>
#include <stdlib.h>
struct pqueue
{
    int value;
    int priority;
}a[50];
int max,front=-1,rear=-1;
void enqueue(int value,int priority)
{
    if (rear==max-1)
    {
        printf("full");
    }
    else if(rear==-1)
    {
        front=0;
        rear=0;
        a[rear].value=value;
        a[rear].priority=priority;
    }
    else
    {
        rear++;
        a[rear].value=value;
        a[rear].priority=priority;
        for(int i=rear;a[i].priority<a[i-1].priority;i--)
        {
            int temp=a[i].value;
            a[i].value=a[i-1].value;
            a[i-1].value=temp;
            temp=a[i].priority;
            a[i].priority=a[i-1].priority;
            a[i-1].priority=temp;
        }
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
        printf("deleted element is %d",a[rear]);
        front=-1;
        rear=-1;
    }
    else
    {
        printf("deleted element is %d",a[front]);
        front++;
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
        for (int i=front;i<=rear;i++)
        {
            printf("%d\t",a[i]);
        }
    }
}
void main()
{
    int ch,val,pr;
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
                    printf("\nInput priority:");
                    scanf("%d",&pr);
                    enqueue(val,pr);
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
