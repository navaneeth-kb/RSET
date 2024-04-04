#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *link;
};
struct node *front=NULL,*rear=NULL,*ptr,*temp;
void enqueue(int value)
{
    if (front==NULL)
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->data=value;
        temp->link=NULL;
        front=rear=temp;
    }
    else
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->data=value;
        temp->link=NULL;
        rear->link=temp;
        rear=temp;
    }
}
void dequeue()
{
    if(front==NULL)
    {
        printf("Empty");
    }
    else if(front==rear)
    {
        printf("Deleted data is %d",front->data);
        temp=front;
        front=rear=NULL;
        free(temp);
    }
    else
    {
        temp=front;
        front=front->link;
        free(temp);
    }
}
void display()
{
    if (front==NULL)
    {
        printf("Emptty");

    }
    else
    {
        ptr=front;
        while(ptr!=NULL)
        {
            printf("%d\t",ptr->data);
            ptr=ptr->link;
        }
    }
}
void main()
{
    int ch,val;
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
