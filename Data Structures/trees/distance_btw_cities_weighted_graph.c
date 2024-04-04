#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node 
{
    char data[30];
    struct node* link;
};

struct store 
{
    char ele[30];
    int vis;
};

struct store* p[30];
struct node* arr[30];
int a[30][30] = {0};
int n;
char q[30];
char stack[30];

struct node* createNode(char ele[])
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->data, ele);
    newNode->link = NULL;
    return newNode;
}

void shortest()
{
    int x = 1000;
    int k = 0;
    int l = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0 && x > a[i][j])
            {
                x = a[i][j];
                k = i;
                l = j;
            }
        }
    }
    printf("The shortest cities are %s and %s\n", p[k]->ele, p[l]->ele);
}

void displayAdjacencyMatrix()
{
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void displayAdjacencyList()
{
    struct node* ptr;
    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++)
    {
        ptr = arr[i];
        printf("%s -> ", p[i]->ele);
        while (ptr != NULL)
        {
            printf("%s -> ", ptr->data);
            ptr = ptr->link;
        }
        printf("\n");
    }
}

void main()
{
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the vertices:\n");
    for (int i = 0; i < n; i++)
    {
        p[i] = (struct store*)malloc(sizeof(struct store));
        scanf(" %s", p[i]->ele);
        p[i]->vis = 0;
    }

    struct node* ptr;
    for (int i = 0; i < n; i++)
    {
        arr[i] = createNode(p[i]->ele);
        ptr = arr[i];
        for (int j = 0; j < n; j++)
        {
            printf("Distance between %s and %s: ", p[i]->ele, p[j]->ele);
            scanf("%d", &a[i][j]);

            if (a[i][j] != 0)
            {
                ptr->link = createNode(p[j]->ele);
                ptr = ptr->link;
            }
        }
    }

    while (1)
    {
        int ch;
        printf("1. Shortest Cities\n2. Display Adjacency Matrix\n3. Display Adjacency List\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                shortest();
                break;
            case 2:
                displayAdjacencyMatrix();
                break;
            case 3:
                displayAdjacencyList();
                break;
            default:
                exit(0);
        }
    }
}
