#include <stdio.h>
#include <stdlib.h.>
struct node
{
    int data;
    struct node *link;
};
struct node *top=NULL,*temp,*ptr;
void push(int value)
{
    temp=(struct node *)malloc(sizeof(struct node));
    temp->data=value;
    temp->link=top;
    top=temp;
}
void pop()
{
    if (top==NULL)
    {
        printf("Empty");
    }
    else
    {
        printf("deleted element is %d",top->data);
        temp=top;
        top=top->link;
        free(temp);
    }
}
void display()
{
    if(top==NULL)
    {
        printf("empty");
    }
    else
    {
        ptr=top;
        while(ptr!=NULL)
        {
            printf("%d\t",ptr->data);
            ptr=ptr->link;
        }
    }
}
void main()
{
    int val,ch;
    while(1)
    {
        printf("\n1-PUSH \n2-POP \n3-DISPLAY \n4-EXIT");
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\nInput value:");
                    scanf("%d",&val);
                    push(val);
                    break;
            case 2: pop();
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
