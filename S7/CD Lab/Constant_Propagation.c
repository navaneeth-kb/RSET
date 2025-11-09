#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Instruction
{
    char lhs[30],op1[30],op[30],op2[30];
}code[20];

int isConstant(char s[])
{
    for (int i=0;s[i]!='\0';i++)
    {
        if (!isdigit(s[i]))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n;
    printf("Enter the number of instructions:");
    scanf("%d",&n);

    printf("\nEnter instructions:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%s = %s %s %s",code[i].lhs,code[i].op1,code[i].op,code[i].op2);
    }

    for (int i=0;i<n;i++)
    {
        if (isConstant(code[i].op1) && isConstant(code[i].op2))
        {
            int val1=atoi(code[i].op1);
            int val2=atoi(code[i].op2);

            int ans;
            if (strcmp(code[i].op,"+")==0)
            {
                ans=val1+val2;
            }
            else if (strcmp(code[i].op,"-")==0)
            {
                ans=val1-val2;
            }
            else if (strcmp(code[i].op,"*")==0)
            {
                ans=val1*val2;
            }
            else if (strcmp(code[i].op,"/")==0)
            {
                ans=val1/val2;
            }

            sprintf(code[i].op1,"%d",ans);
            strcpy(code[i].op,"");
            strcpy(code[i].op2,"");
        }

        for (int j=i+1;j<n;j++)
        {
            if(strcmp(code[j].op1,code[i].lhs)==0 && isConstant(code[i].op1))
            {
                strcpy(code[j].op1,code[i].op1);
            }
            if(strcmp(code[j].op2,code[i].lhs)==0 && isConstant(code[i].op1))
            {
                strcpy(code[j].op2,code[i].op1);
            }
        }
    }

    printf("\nOptimized Code:\n");
    for (int i=0;i<n;i++)
    {
        if (strlen(code[i].op)==0)
        {
            printf("%s = %s\n",code[i].lhs,code[i].op1);
        }
        else
        {
            printf("%s = %s %s %s\n",code[i].lhs,code[i].op1,code[i].op,code[i].op2);
        }
    }

    return 0;
}
