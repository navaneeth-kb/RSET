#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Production{
    char left[10];
    char right[10];
};

int main()
{
    int prod_num;
    struct Production p[10];
    char prod_str[10];

    printf("Enter the number of productions:");
    scanf("%d",&prod_num);
    for (int i=0;i<prod_num;i++)
    {
        printf("Enter production %d (e.g., E->E+T): ", i + 1);
        scanf("%s",prod_str);

        char *lhs=strtok(prod_str,"->");
        char *rhs=strtok(NULL,"->");

        strcpy(p[i].left,lhs);
        strcpy(p[i].right,rhs);
    }

    char input[10];
    printf("Enter the input string: ");
    scanf("%s", input);

    char stack[10],curr[10];
    stack[0]='\0';
    curr[0]='\0';
    int ind=0;

    printf("\n--- Shift Reduce Parsing Steps ---\n\n");
    while(1)
    {
        //Shift
        if (ind<strlen(input))
        {
            curr[0]=input[ind];
            curr[1]='\0';
            ind++;

            strcat(stack,curr);

            printf("Stack:%s   Input:%s   Action:Shift\n",stack,input+ind);
        }

        //Reduce
        int reduced=0;
        for (int i=0;i<prod_num;i++)
        {
            char *found=strstr(stack,p[i].right);;
            if (found!=NULL)
            {
                int right_len=strlen(p[i].right);
                int stack_len=strlen(stack);

                int temp=stack_len-right_len;
                stack[temp]='\0';
                strcat(stack,p[i].left);

                printf("Stack:%s   Input:%s   Action:Reduce from %s to %s\n",stack,input+ind,p[i].left,p[i].right);

                reduced=1;
                i=-1;
            }
        }

        // --- Check for Acceptance or Rejection ---
        if (strcmp(stack, p[0].left) == 0 && ind == strlen(input)) {
            printf("\nParsing Successful!\n");
            break;
        }
        else if (ind == strlen(input) && !reduced) {
            printf("\nParsing Failed.\n");
            break;
        }
    }

    return 0;
}
