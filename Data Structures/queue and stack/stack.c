#include <stdio.h>
#include<stdlib.h>
int a[50],top=-1,max;
void push(int value)
{
    if (top==max-1)
    {
        printf("full");
    }
    else
    {
        top++;
        a[top]=value;
    }
}
void pop()
{
    if (top==-1)
    {
        printf("empty");
    }
    else
    {
        printf("deleted:%d",a[top]);
        top--;
    }
}
void display()
{
    if(top==-1)
    {
        printf("empty");
    }
    else
    {
        for(int i=0;i<=top;i++)
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
