#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *rlink;
    struct node *llink;
};
struct node *ptr,*head=NULL,*temp;
void insert_front(int value)
{
    if (head==NULL)
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->data=value;
        temp->rlink=temp->llink=NULL;
        head=temp;
    }
    else
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->data=value;
        temp->rlink=head;
        temp->llink=NULL;
        head->llink=temp;
        head=temp;
    }
}
void insert_rear(int value)
{
    if (head==NULL)
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->data=value;
        temp->rlink=temp->llink=NULL;
        head=temp;
    }
    else
    {
        ptr=head;
        while(ptr->rlink!=NULL)
        {
            ptr=ptr->rlink;
        }
        temp=(struct node *)malloc(sizeof(struct node));
        temp->data=value;
        temp->rlink=NULL;
        temp->llink=ptr;
        ptr->rlink=temp;
    }
}
void insert_node(int value,int key)
{
    if(head==NULL)
    {
        printf("empty");
    }
    else
    {
        ptr=head;
        while(ptr->data!=key && ptr->rlink!=NULL)
        {
            ptr=ptr->rlink;
        }
        if (ptr->data!=key)
        {
            printf("Node not found");
        }
        else
        {
            temp=(struct node *)malloc(sizeof(struct node));
            temp->data=value;
            temp->rlink=ptr->rlink;
            temp->llink=ptr;
            if(temp->rlink!=NULL)
            {
                ptr->rlink->llink=temp;
            }
            ptr->rlink=temp;
        }
    }
}
void delete_front()
{
    if (head==NULL)
    {
        printf("Empty");
    }
    else if(head->rlink==NULL)
    {
        temp=head;
        head=NULL;
        free(temp);
    }
    else
    {
        temp=head;
        head=head->rlink;
        head->llink=NULL;
        free(temp);
    }
}
void delete_rear()
{
    if (head==NULL)
    {
        printf("Empty");
    }
    else if(head->rlink==NULL)
    {
        temp=head;
        head=NULL;
        free(temp);
    }
    else
    {
        ptr=head;
        while(ptr->rlink->rlink!=NULL)
        {
            ptr=ptr->rlink;
        }
        temp=ptr->rlink;
        ptr->rlink=NULL;
        temp->llink=NULL;
        free(temp);
    }
}
void delete_node(int key)
{
    if(head==NULL)
    {
        printf("Empty");
    }
    else if(head->data==key)
    {
        temp=head;
        head=head->rlink;
        free(temp);
    }
    else
    {
        ptr=head;
        while(ptr->data!=key && head->rlink!=NULL)
        {
            ptr=ptr->rlink;
        }
        if (ptr->data!=key)
        {
            printf("node not found");
        }
        else
        {
            ptr->llink->rlink=ptr->rlink;
            if (ptr->rlink!=NULL)
            {
                ptr->rlink->llink=ptr->llink;
            }
            free(ptr);
        }
    }
}
// another delete_node method
/*void deleten(int key)
{
    if (head==NULL)
    {
        printf("empty");
    }
    else if(head->data==key)
    {
        temp=head;
        head=head->rlink;;
        free(temp);
    }
    else
    {
        ptr=head;
        while(ptr->rlink->data!=key && ptr->rlink->rlink!=NULL)
        {
            ptr=ptr->rlink;
        }
        if (ptr->rlink->data!=key)
        {
            printf("node not found");
        }
        else
        {
            temp=ptr->rlink;
            ptr->rlink=ptr->rlink->rlink;
            if(ptr->rlink!=NULL)
            {
                ptr->rlink->llink=ptr;
            }
            free(temp);
        }
    }
}*/
void display_front()
{
    ptr=head;
    while(ptr!=NULL)
    {
        printf("%d\t",ptr->data);
        ptr=ptr->rlink;
    }
}
void display_rear()
{
    if (head == NULL)
    {
        printf("Empty");
        return;
    }
    else
    {
        ptr= head;
        while (ptr->rlink != NULL)
        {
            ptr = ptr->rlink;
        }

        while (ptr != NULL)
        {
            printf("%d\t", ptr->data);
            ptr = ptr->llink;
        }
        printf("%d", ptr->data);
    }
}
void main()
{
    int op,val,key;
    while(1)
    {
        printf("\n");
        printf("\n1.INSERT AT BEGINNING  \n2.INSERT AT END     \n3.INSERT AT A SPECIFIED NODE  \n4.DELETE FROM BEGINNING     \n5.DELETE FROM END   \n6.DELETE A SPECIFIED NODE     \n7.DISPLAY FRONT \n8-DISPLAY REAR  \n9.EXIT");
        printf("\nEnter choice:");
        scanf("%d",&op);
        switch(op)
        {
            case 1: printf("enter value:");
                    scanf("%d",&val);
                    insert_front(val);
                    break;
            case 2: printf("enter value:");
                    scanf("%d",&val);
                    insert_rear(val);
                    break;
            case 3: printf("enter value:");
                    scanf("%d",&val);
                    printf("Enter key:");
                    scanf("%d",&key);
                    insert_node(val,key);
                    break;
            case 4: delete_front();
                    break;
            case 5: delete_rear();
                    break;
            case 6: printf("Enter key:");
                    scanf("%d",&key);
                    delete_node(key);
                    break;
            case 7:display_front();
                    break;
            case 8: display_rear();
                    break;
            case 9:exit(0);
        }
    }
}
