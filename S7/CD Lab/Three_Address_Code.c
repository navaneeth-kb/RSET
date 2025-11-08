#include <stdio.h>
#include <ctype.h>
#include <string.h>

char postfix[100];
char st[100];
int top=-1;

void push(char c)
{
    top++;
    st[top]=c;
}

char pop()
{
    return st[top--];
}

int precedence(char c)
{
    if (c=='+' || c=='-')
    {
        return 1;
    }
    if (c=='*' || c=='/')
    {
        return 2;
    }
    return 0;
}

void InfixToPostfix(char infix[],char post[])
{
    int i,k=0;
    char ch;
    for (i=0;infix[i]!='\0';i++)
    {
        ch=infix[i];
        if (isalnum(ch))
        {
            post[k++]=ch;
        }
        else if (ch=='(')
        {
            push(ch);
        }
        else if(ch==')')
        {
            while (top!=-1 && st[top]!='(')
            {
                post[k++]=pop();
            }
            pop();
        }
        else if (ch=='+' || ch=='-' || ch=='*' || ch=='/')
        {
            while (top!=-1 && precedence(st[top])>=precedence(ch))
            {
                post[k++]=pop();
            }
            push(ch);
        }
    }
    while (top!=-1)
    {
        post[k++]=pop();
    }
    post[k]='\0';
}

void GenerateTAC(char post[],char lhs)
{
    char st[100][100];
    int t=-1;
    int tempCount=0;
    char temp[3];

    for (int i=0;post[i]!='\0';i++)
    {
        char ch=post[i];
        if (isalnum(ch))
        {
            char str[2]={ch,'\0'};
            strcpy(st[++t],str);
        }
        else
        {
            char op1[100],op2[100];
            strcpy(op1,st[t--]);
            strcpy(op2,st[t--]);
            sprintf(temp,"T%d",++tempCount);
            printf("%s = %s %c %s\n",temp,op1,ch,op2);
            strcpy(st[++t],temp);
        }
    }
    printf("%c = %s\n",lhs,st[t]);
}

int main()
{
    char expr[100];
    printf("Enter the expression:");
    scanf("%s",expr);

    char lhs=expr[0];
    char rhs[100];
    strcpy(rhs,expr+2);

    char postfix[100];
    InfixToPostfix(expr,postfix);
    GenerateTAC(postfix,lhs);
}
