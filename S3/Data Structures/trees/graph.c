#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node *link;
};
struct store
{
    char ele;
    int vis;
};

struct store *p[30];
struct node *arr[30];    // Adjacency list
int a[20][20]={0};   //Adjacency matrix 
int n;  //Max  value
char q[30];     //BFS Traversal
char stk[30];   //DFS Traversal

struct node *createNode(char c)
{
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->data=c;
    temp->link=NULL;
    return temp;
}

void adjacencyMatrix()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
}

void adjacencyList()
{
    struct node *ptr;
    for(int i=0;i<n;i++)
    {
        ptr=arr[i];
        printf("%d.",i);
        while(ptr!=NULL)
        {
            printf("%c\t",ptr->data);
            ptr=ptr->link;
        }
        printf("\n");
    }
}

int front=0,rear=-1;
void enqueue(char val)
{
    rear++;
    q[rear]=val;
}
char dequeue()
{
    char y=q[front];
    front++;
    return y;
}
void BFS()
{
    char s;
    int i,j;
    struct node *ptr;
    printf("Enter source:");
    scanf(" %c",&s);
    for(i=0;i<n;i++)
    {
        if (p[i]->ele==s)
        {
            enqueue(s);
            p[i]->vis=1;
        }
    }
    int count=1;
    while(count!=0)
    {
        char x=dequeue();
        printf("%c",x);
        count--;
        for(i=0;i<n;i++)
        {
            if(arr[i]->data==x)
            {
                ptr=arr[i]->link;
                while(ptr!=NULL)
                {
                    for(j=0;j<n;j++)
                    {
                        if(ptr->data==p[j]->ele && p[j]->vis==0)
                        {
                            enqueue(ptr->data);
                            count++;
                            p[j]->vis=1;
                        }
                    }
                    ptr=ptr->link;
                }
            }
        }
    }
}

int top=0;
void push(char val)
{
    stk[top]=val;
    top++;
}
char pop()
{
    char y=stk[top-1];
    top--;
    return y;
}
void DFS()
{
    char s;
    int i,j;
    struct node *ptr;
    printf("Enter source:");
    scanf(" %c",&s);
    for(i=0;i<n;i++)
    {
        if (p[i]->ele==s)
        {
            push(s);
            p[i]->vis=1;
        }
    }
    int count=1;
    while(count!=0)
    {
        char x=pop();
        printf("%c ",x);
        count--;
        for(i=0;i<n;i++)
        {
            if(arr[i]->data==x)
            {
                ptr=arr[i]->link;
                while(ptr!=NULL)
                {
                    for(j=0;j<n;j++)
                    {
                        if(ptr->data==p[j]->ele && p[j]->vis==0)
                        {
                            push(ptr->data);
                            count++;
                            p[j]->vis=1;
                        }
                    }
                    ptr=ptr->link;
                }
            }
        }
    }
}

void main()
{

    printf("Enter no of vertices:");
    scanf("%d",&n);
    printf("enter vertices values:");
    for(int i=0;i<n;i++)
    {
        p[i]=(struct store*)malloc(sizeof(struct store));
        scanf(" %c",&p[i]->ele);
        p[i]->vis=0;
    }

    int z;
    struct node *ptr;
    for(int i=0;i<n;i++)
    {
        arr[i]=createNode(p[i]->ele);
        ptr=arr[i];
        for(int j=0;j<n;j++)
        {
            printf("%c => %c if there is a link input 1, else 0:",p[i]->ele,p[j]->ele);
            scanf("%d",&z);
            if(z==1)
            {
                ptr->link=createNode(p[j]->ele);
                ptr=ptr->link;
                a[i][j]=1;
            }
        }
    }
    while (1)
    {
        int ch;
        printf("1. Adjacency Matrix Representation\n2. Adjacency List Representation\n3. BFS traversal\n4. DFS traversal\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                adjacencyMatrix();
                break;
            case 2:
                adjacencyList();
                break;
            case 3:
                BFS();
                for (int i = 0; i < n; i++) {
                    p[i]->vis = 0;
                }
                printf("\n");
                break;
            case 4:
                DFS();
                for (int i = 0; i < n; i++) {
                    p[i]->vis = 0;
                }
                printf("\n");
                break;
            default:
                exit(0);
        }
    }
}
