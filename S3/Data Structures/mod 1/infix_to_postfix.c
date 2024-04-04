#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char a[100],b[100],c[100];
int top=-1,max;
/* a - expression we input
   b[] - postfix stack
   c[] - operator stack (temporary)
   d[] - evaluation stack
   j - variable to traverse postfix stack
*/
void push(char ch)
{
    top++;
    c[top]=ch;
}
char pop()
{
    char value=c[top];
    top--;
    return value;
}
int priority(char ch)
{
    switch(ch)
    {
        case '^':return(3);
                break;
        case '*': return(2);
                break;
        case '/': return(2);
                break;
        case '+': return (1);
                break;
        case '-':return (1);
                break;
        default: return(0);
                break;
    }
}
int etop=-1,k,d[100];
void epush(int value)
{
    etop++;
    d[etop]=value;
}
int epop()
{
    int evalue=d[etop];
    etop--;
    return evalue;
}
void main()
{
    int i=0,j=0;
    char exp;
    printf("enter expression:");
    gets(a);
    for(i=0;a[i]!='\0';i++)
    {
        if (a[i]=='(')
        {
            push(a[i]);
        }
        else if((a[i]>='a' && a[i]<='z')||(a[i]>='A' && a[i]<='Z'))
        {
            b[j]=a[i];
            j++;
        }
        else if(a[i]==')')
        {
            while(c[top]!='(')
            {
                exp=pop();
                b[j]=exp;
                j++;
            }
            exp=pop();
        }
        else
        {
            if(priority(a[i])<=priority(c[top]))
            {
                b[j]=pop();

                j++;
            }
            push(a[i]);
        }
    }
    b[j]='\0';
    printf("the postfix notation:");
    puts(b);
    int r;
    for(j=0;b[j]!='\0';j++)
    {
        if((b[j]>='a' && b[j]<='z')||(b[j]>='A' && b[j]<='Z'))
        {
            printf("Enter the value of the variable %c:",b[j]);
            scanf("%d",&i);
            epush(i);
        }
        else
        {
            int y=epop();
            int x=epop();
            switch(b[j])
            {
                case '+': r=x+y;
                            break;
                case '-': r=x-y;
                            break;
                case '*': r=x*y;
                            break;
                case '/': r=x/y;
                            break;
                case '^': r=x^y;
                            break;

            }
            epush(r);
        }
    }
    int ans;
    ans=epop();
    printf("result is %d",ans);
}
