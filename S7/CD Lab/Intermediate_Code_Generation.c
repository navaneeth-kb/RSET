#include <stdio.h>
#include <string.h>

int main()
{
    //input
    printf("Enter the Three Address Code (type 'exit' to stop):\n");
    char tac[100][100];
    int count=0;

    while(1)
    {
        printf(">");
        fgets(tac[count],sizeof(tac[count]),stdin);
        tac[count][strcspn(tac[count],"\n")]='\0';
        if (strcmp(tac[count], "exit")==0)
        {
            break;
        }
        count++;
    }

    printf("\n--- Target Code Generation ---\n");

    for(int i=0;i<count;i++)
    {
        char lhs[30],op1[30],op2[30],line[100],op;

        strcpy(line,tac[i]);
        char clean[100];
        int idx=0,j=0;  //clean index
        for (j=0;line[j]!='\0';j++)
        {
            if (line[j]!=' ')
            {
                clean[idx++]=line[j];
            }
        }
        clean[idx]='\0';

        printf("\nTAC => %s\n",clean);

        int eq_pos=-1;
        for (int j=0;clean[j]!='\0';j++)
        {
            if (clean[j]=='=')
            {
                eq_pos=j;
                break;
            }
        }

        strncpy(lhs,clean,eq_pos);
        lhs[eq_pos]='\0';

        int op_pos=-1;
        for (int j=0;clean[j]!='\0';j++)
        {
            if (clean[j]=='+' || clean[j]=='-' || clean[j]=='*' || clean[j]=='/')
            {
                op_pos=j;
                op=clean[j];
                break;
            }
        }

        if (op_pos!=-1)
        {
            strncpy(op1,clean + eq_pos + 1,op_pos - eq_pos - 1);
            op1[op_pos- eq_pos -1]='\0';
            strcpy(op2,clean+op_pos+1);

            printf("MOV AX,[%s]\n",op1);
            if (op=='+')
            {
                printf("ADD AX,[%s]\n",op2);
            }
            else if (op=='-')
            {
                printf("SUB AX,[%s]\n",op2);
            }
            else if (op=='*')
            {
                printf("MUL AX,[%s]\n",op2);
            }
            else if (op=='/')
            {
                printf("DIV AX,[%s]\n",op2);
            }

            printf("MOV [%s], AX\n", lhs);
        }
        else
        {
            strcpy(op1, clean + eq_pos + 1);
            printf("MOV AX,[%s]\n",op1);
            printf("MOV [%s],AX\n",lhs);
        }
    }
    return 0;
}
