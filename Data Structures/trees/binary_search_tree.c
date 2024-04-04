#include <stdio.h>
#include <stdlib.h>
struct node
{
  int data;
  struct node *left;
  struct node *right;
};
struct node *temp,*ptr,*root=NULL;
struct node *create_node(int value)
{
    temp=(struct node *)malloc(sizeof(struct node));
    temp->data=value;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct node *insert_node(struct node *root,int value)
{
    if(root==NULL)
    {
        return create_node(value);
    }
    else if(value>root->data)
    {
        root->right=insert_node(root->right,value);
    }
    else if(value<root->data)
    {
        root->left=insert_node(root->left,value);
    }
    return root;
}
struct node *min_root(struct node *ptr)
{
    while(ptr->left!=NULL)
    {
        ptr=ptr->left;
    }
    return ptr;
}
struct node *search_node(struct node *root,int value)
{
    if (root==NULL)
    {
        return root;
    }
    else if(value>root->data)
    {
        return search_node(root->right,value);
    }
    else if(value<root->data)
    {
        return search_node(root->left,value);
    }
}
struct node *delete_node(struct node *root,int key)
{
    if (root==NULL)
    {
        return root;
    }
    else if(key>root->data)
    {
        root->right=delete_node(root->right,key);
    }
    else if(key<root->data)
    {
        root->left=delete_node(root->left,key);
    }
    else
    {
        if (root->left==NULL)
        {
            temp=root->right;
            free(root);
            return temp;
        }
        else if (root->right==NULL)
        {
            temp=root->left;
            free(root);
            return temp;
        }
        else
        {
            temp=min_root(root->right);
            root->data=temp->data;
            root->right=delete_node(root->right,temp->data);
        }
    }
    return root;
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
//Non-recursive
/*
void preorder(struct node *root)
{
    if (root==NULL)
    {
        return;
    }
    struct node *stk[100];
    int top=-1;
    while(root!=NULL || top>=0)
    {
        while(root!=NULL)
        {
            printf("%d",root->data);
            stk[++top]=root;
            root=root->left;
        }
        root=stk[top--]->right;

    }
}
void inorder(struct node *root)
{
    if (root==NULL)
    {
        return;
    }
    struct node *stk[100];
    int top=-1;
    while(root!=NULL || top>=0)
    {
        while(root!=NULL)
        {

            stk[++top]=root;
            root=root->left;
        }
        root=stk[top--];
        printf("%d",root->data);
        root=root->right;

    }
}
void postorder(struct node *root)
{
    if (root==NULL)
    {
        return;
    }
    struct node *stk[100];
    int top=-1;
    struct node *prev=NULL;
    while(root!=NULL || top>=0)
    {
        while(root!=NULL)
        {

            stk[++top]=root;
            root=root->left;
        }
        root=stk[top--];
        if(root->right==NULL || root->right==prev)
        {
            printf("%d",root->data);
            prev=root;
            root=NULL;
        }
        else
        {
            stk[++top]=root;
            root=root->right;
        }
    }
}
*/

void main()
{
    int n, op;
    while (1)
    {
        printf("\n1.Insert\n2.Delete\n3.Inorder\n4.Preorder\n5.Postorder\n6.Search\n7.exit\nEnter your choice: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("Enter the element to insert: ");
            scanf("%d", &n);
            root = insert_node(root, n);
            break;
        case 2:
            printf("Enter the element to delete: ");
            scanf("%d", &n);
            root = delete_node(root, n);
            break;
        case 3:
            printf("Inorder: ");
            inorder(root);
            printf("\n");
            break;
        case 4:
            printf("Preorder: ");
            preorder(root);
            printf("\n");
            break;
        case 5:
            printf("Postorder: ");
            postorder(root);
            printf("\n");
            break;
        case 6:
            printf("Enter the element to search: ");
            scanf("%d", &n);
            if(search_node(root,n)!=NULL)
            {
                printf("found");
            }
            else
            {
                printf("not found");
            }
            break;
        case 7: exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
}
