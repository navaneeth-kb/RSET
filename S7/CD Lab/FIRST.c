#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char prod[20][20];
int n;

void addToSet(char first[],char lhs)
{
    int found=0;
    for (int i=0;first[i]!='\0';i++)
    {
        if (first[i]==lhs)
        {
            found=1;
            break;
        }
    }
    if (!found)
    {
        int l=strlen(first);
        first[l]=lhs;
        first[l+1]='\0';
    }
}

void findFirst(char first[],char lhs)
{
    if (!isupper(lhs))
    {
        addToSet(first,lhs);
        return;
    }
    for (int i=0;i<n;i++)
    {
        if (prod[i][0]!=lhs)
        {
            continue;
        }

        int rhsIndex=2;

        if (prod[i][rhsIndex]=='#')
        {
            addToSet(first,'#');
            continue;
        }

        while (prod[i][rhsIndex]!='\0')
        {
            char curr=prod[i][rhsIndex];

            if (!isupper(curr))
            {
                addToSet(first,curr);
                break;
            }

            char temp[20]="";
            findFirst(temp,curr);

            for (int k=0;temp[k]!='\0';k++)
            {
                if (temp[k]!='#')
                {
                    addToSet(first,temp[k]);
                }
            }

            int hasEpsilon=0;
            for (int k=0;temp[k]!='\0';k++)
            {
                if (temp[k]=='#')
                {
                    hasEpsilon=1;
                    break;
                }
            }

            if (!hasEpsilon)
            {
                break;
            }
            else if (prod[i][rhsIndex+1]=='\0')
            {
                addToSet(first,'#');
            }
            rhsIndex++;
        }
    }
}

int main()
{
    printf("Enter the number of productions:");
    scanf("%d",&n);

    printf("Enter productions:\n");
    for (int i=0;i<n;i++)
    {
        scanf("%s",prod[i]);
    }

    int visited[256]={0};

    for (int i=0;i<n;i++)
    {
        char lhs=prod[i][0];
        if (!visited[(int)lhs])
        {
            char first[20]="";
            findFirst(first,lhs);

            printf("FIRST(%c) = { ",lhs);
            for (int j=0;first[j]!='\0';j++)
            {
                printf("%c ",first[j]);
            }
            printf("}\n");

            visited[(int)lhs]=1;
        }
    }
}
