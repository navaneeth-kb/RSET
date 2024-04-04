#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *link;
};
struct node *ptr,*head=NULL,*temp,*prev,*curr;
void front_insert(int value)
{
    if (head==NULL)
    {
        temp=(struct node*)malloc(sizeof(struct node));
        temp->data=value;
        temp->link=NULL;
        head=temp;
    }
    else
    {
        temp=(struct node*)malloc(sizeof(struct node));
        temp->data=value;
        temp->link=head;
        head=temp;
    }
}
void rear_insert(int value)
{
    if (head==NULL)
    {
        temp=(struct node*)malloc(sizeof(struct node));
        temp->data=value;
        temp->link=NULL;
        head=temp;
    }
    else
    {
        ptr=head;
        while(ptr->link!=NULL)
        {
            ptr=ptr->link;
        }
        temp=(struct node*)malloc(sizeof(struct node));
        temp->data=value;
        temp->link=NULL;
        ptr->link=temp;
    }
}
void node_insert(int value, int key)
{
    if(head==NULL)
    {
        printf("Node not found");
    }
    else
    {
        ptr=head;
        while(ptr->data!=key && ptr->link!=NULL)
        {
            ptr=ptr->link;
        }
        if(ptr->data!=key)
        {
            printf("Node not found");
        }
        else
        {
            temp=(struct node*)malloc(sizeof(struct node));
            temp->data=value;
            temp->link=ptr->link;
            ptr->link=temp;
        }
    }
}
void front_delete()
{
    if(head==NULL)
    {
        printf("Empty");
    }
    else
    {
        //temp=(struct node*)malloc(sizeof(struct node));
        temp=head;
        head=head->link;
        free(temp);
    }
}
void rear_delete()
{
    if(head==NULL)
    {
        printf("Empty");
    }
    else if(head->link==NULL)
    {
        //temp=(struct node*)malloc(sizeof(struct node));
        temp=head;
        head=head->link;
        free(temp);
    }
    else
    {
        prev=head;
        curr=head->link;
        while(curr->link!=NULL)
        {
            prev=curr;
            curr=curr->link;
        }
        prev->link=NULL;
        free(curr);
    }
}
void node_delete(int key)
{
    if(head==NULL)
    {
        printf("Empty");
    }
    else if(head->data==key)
    {
        //temp=(struct node*)malloc(sizeof(struct node));
        temp=head;
        head=head->link;
        free(temp);
    }
    else
    {
        ptr=head;
        while(ptr->link->data!=key && ptr->link->link!=NULL)
        {
            ptr=ptr->link;
        }
        if (ptr->link->data!=key)
        {
            printf("Node not found");
        }
        else
        {
            printf("Deleted data is %d",ptr->link->data);
            //temp=(struct node*)malloc(sizeof(struct node));
            temp=ptr->link;
            ptr->link=ptr->link->link;
            free(temp);
        }

    }
}
void display()
{
    if(head==NULL)
    {
        printf("Empty");
    }
    else
    {
        ptr=head;
        while(ptr!=NULL)
        {
            printf("%d\t",ptr->data);
            ptr=ptr->link;
        }
    }
}
void main()
{
    int op,val,key;
    while(1)
    {
        printf("\n");
        printf("\n1.INSERT AT BEGINNING  \n2.INSERT AT END     \n3.INSERT AT A SPECIFIED NODE  \n4.DELETE FROM BEGINNING     \n5.DELETE FROM END   \n6.DELETE A SPECIFIED NODE     \n7.DISPLAY  \n8.EXIT");
        printf("\nEnter choice:");
        scanf("%d",&op);
        switch(op)
        {
            case 1: printf("enter value:");
                    scanf("%d",&val);
                    front_insert(val);
                    break;
            case 2: printf("enter value:");
                    scanf("%d",&val);
                    rear_insert(val);
                    break;
            case 3: printf("enter value:");
                    scanf("%d",&val);
                    printf("Enter key:");
                    scanf("%d",&key);
                    node_insert(val,key);
                    break;
            case 4: front_delete();
                    break;
            case 5: rear_delete();
                    break;
            case 6: printf("Enter key:");
                    scanf("%d",&key);
                    node_delete(key);
                    break;
            case 7:display();
                    break;
            case 8:exit(0);
        }
    }
}
