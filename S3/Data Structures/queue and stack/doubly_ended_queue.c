#include <stdio.h>
int a[50],front=-1,rear=-1,max;
void front_insert(int value)
{
    if (rear==max-1)
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
        for(int i=rear;i>=front;i--)
        {
            a[i+1]=a[i];
        }
        a[front]=value;
        rear++;
    }
}
void rear_insert(int value)
{
    if(rear==max-1)
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
        rear++;
        a[rear]=value;
    }
}
void front_delete()
{
    if(rear==-1)
    {
        printf("empty");
    }
    else if(front==rear)
    {
        printf("deleted element is %d",a[rear]);
        rear=-1;
        front=-1;
    }
    else
    {
        printf("deleted element is %d",a[front]);
        front++;
    }

}
void rear_delete()
{
    if(rear==-1)
    {
        printf("empty");
    }
    else if(front==rear)
    {
        printf("deleted element is %d",a[rear]);
        rear=-1;
        front=-1;
    }
    else
    {
        printf("deleted element is %d",a[rear]);
        rear--;
    }
}
void display()
{
    if(rear==-1)
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
        printf("\n1-FRONT INSERT \n2-REAR INSERT \n3-FRONT DELETE \n4-REAR DELETE \n5-DISPLAY \n6-EXIT");
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\nInput value:");
                    scanf("%d",&val);
                    front_insert(val);
                    break;
            case 2: printf("\nInput value:");
                    scanf("%d",&val);
                    rear_insert(val);
                    break;
            case 3: front_delete();
                    break;
            case 4: rear_delete(0);
                    break;
            case 5: display();
                    break;
            case 6: exit(0);
            default: printf("invalid choice");
                     break;
        }
    }
}
