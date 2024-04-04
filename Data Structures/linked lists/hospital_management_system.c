#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct node
{
    int token;
    char name[50];
    struct node *link;
};
struct node *temp,*ptr,*front=NULL,*rear=NULL;
void add(char nam[])
{
    if(front==NULL)
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->token=1;
        strcpy(temp->name,nam);
        temp->link=NULL;
        front=rear=temp;
    }
    else
    {
        temp=(struct node *)malloc(sizeof(struct node));
        temp->token=rear->token+1;
        strcpy(temp->name,nam);
        temp->link=NULL;
        rear->link=temp;
        rear=temp;
    }

}
void deletee()
{
    if(front==NULL)
    {
        printf("empty");
    }
    else if (front==rear)
    {
        temp=front;
        front=rear=NULL;
        free(temp);
    }
    else
    {
        temp=front;
        front=front->link;;
        free(temp);
    }
}
void display()
{
    if(front==NULL)
    {
        printf("empty");
    }
    else
    {
        ptr=front;
        while(ptr!=NULL)
        {
            printf("%d\t",ptr->token);
            printf("%s\t",ptr->name);
            ptr=ptr->link;
            printf("\n");
        }


    }
}
void next()
{
    if(front==NULL)
    {
        printf("empty");
    }
    else
    {
        printf("Next:");
        printf("%d",front->token);
    }
}
void main()
{
        int choice;
        char nam[50];
    while (1) {
        printf("\nDoctor Consultation Booking System\n");
        printf("1. Add Patient\n");
        printf("2. Delete Patient\n");
        printf("3. Display Next Token\n");
        printf("4. Display Patient List\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name:");
                scanf("%s",nam);

                add(nam);
                break;
            case 2:
                deletee();
                break;
            case 3:
                next();
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

}
