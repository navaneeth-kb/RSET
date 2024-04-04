#include <stdio.h>
#include <stdlib.h>
struct node
{
  int coef;
  int expo;
  struct node *link;
};
struct node *ptr=NULL,*ptr1,*ptr2,*ptr3,*temp=NULL,*phead=NULL,*qhead=NULL,*ahead=NULL,*mhead=NULL;
struct node *read_poly()
{
    struct node *head=NULL;
    int n,i;
    printf("\nEnter num of terms of poly:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        temp=(struct node *)malloc(sizeof(struct node));
        printf("Enter coef and expo:");
        scanf("%d%d",&temp->coef,&temp->expo);
        temp->link=NULL;
        if(head==NULL)
        {
            head=temp;
            ptr=temp;
        }
        else
        {
            ptr->link=temp;
            ptr=temp;
        }
    }
    return head;
}
void display(struct node *head)
{
    if (head==NULL)
    {
        printf("Empty");
    }
    else
    {
        ptr=head;
        while(ptr->link!=NULL)
        {
            printf("%dx^%d+",ptr->coef,ptr->expo);
            ptr=ptr->link;
        }
        printf("%dx^%d",ptr->coef,ptr->expo);
    }
}
struct node *add_poly()
{
    struct node *head=NULL,*ptr3=NULL;
    ptr1=phead;
    ptr2=qhead;
    while(ptr1!=NULL && ptr2!=NULL)
    {
        if (ptr1->expo>ptr2->expo)
        {
            temp=(struct node *)malloc(sizeof(struct node));
            temp->coef=ptr1->coef;
            temp->expo=ptr1->expo;
            temp->link=NULL;
            ptr1=ptr1->link;
        }
        else if (ptr1->expo<ptr2->expo)
        {
            temp=(struct node *)malloc(sizeof(struct node));
            temp->coef=ptr2->coef;
            temp->expo=ptr2->expo;
            temp->link=NULL;
            ptr2=ptr2->link;
        }
        else
        {
            temp=(struct node *)malloc(sizeof(struct node));
            temp->coef=ptr1->coef+ptr2->coef;
            temp->expo=ptr1->expo;
            temp->link=NULL;
            ptr1=ptr1->link;
            ptr2=ptr2->link;
        }
        if (head==NULL)
        {
            head=temp;
            ptr3=temp;
        }
        else
        {
            ptr3->link=temp;
            ptr3=temp;
        }
    }
    while(ptr1!=NULL)
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->coef=ptr1->coef;
        temp->expo=ptr1->expo;
        temp->link=NULL;
        ptr1=ptr1->link;
        if (head==NULL)
        {
            head=temp;
            ptr3=temp;
        }
        else
        {
            ptr3->link=temp;
            ptr3=temp;
        }
    }
    while(ptr2!=NULL)
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->coef=ptr2->coef;
        temp->expo=ptr2->expo;
        temp->link=NULL;
        ptr2=ptr2->link;
        if (head==NULL)
        {
            head=temp;
            ptr3=temp;
        }
        else
        {
            ptr3->link=temp;
            ptr3=temp;
        }
    }
    return head;
}
struct node *multiply_poly()
{
    struct node *head=NULL;
    ptr1=phead;
    ptr2=qhead;
    while(ptr1!=NULL)
    {
        while(ptr2!=NULL)
        {
            temp=(struct node *)malloc(sizeof(struct node ));
            temp->coef=ptr1->coef*ptr2->coef;
            temp->expo=ptr1->expo+ptr2->expo;
            temp->link=NULL;
            if (head==NULL)
            {
                head=temp;
                ptr3=temp;
            }
            else
            {
                ptr3->link=temp;
                ptr3=temp;
            }
            ptr2=ptr2->link;
        }
        ptr1=ptr1->link;
        ptr2=qhead;
    }
    //removing duplicates
    struct node *a=head,*prev,*b;
    while(a!=NULL)
    {
        prev=a;
        b=a->link;
        while(b!=NULL)
        {
            if(a->expo==b->expo)
            {
                a->coef=a->coef+b->coef;
                prev->link=b->link;
                b=prev->link;
            }
            else
            {
                prev=b;
                b=b->link;
            }
        }
        a=a->link;
    }
    return head;
}
void main()
{
    printf("\nEnter 1st poly:");
    phead=read_poly();
    printf("\nInput 2nd poly:");
    qhead=read_poly();
    printf("\n1st poly:");
    display(phead);
    printf("\n2nd poly:");
    display(qhead);
    while(1)
    {
        int ch;
        printf("\n1-ADD \n2-MULTIPLY\n");
        printf("Enter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: ahead=add_poly();
                    display(ahead);
                    break;
            case 2: mhead=multiply_poly();
                    display(mhead);
                    break;
            case 3: exit(0);

        }
    }
}
