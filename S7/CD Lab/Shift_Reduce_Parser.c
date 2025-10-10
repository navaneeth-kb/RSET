# include<stdio.h>
# include<string.h>
# include<stdlib.h>

struct pro
{
    char left[10];
    char right[10];
};

void main()
{
    int i=0,top,sl,subl,rule,j=0;
    char *token1,*token2,*sub,input[20],ch[20],stack[20],production[20];
    struct pro p[10];
    printf("Enter the total no of productions");
    scanf("%d",&rule);
    for(int i=0;i<rule;i++)
    {
        printf("Enter the %d production\n",i+1);
        scanf("%s",production);
        token1=strtok(production,"->");
        token2=strtok(NULL,"->");
        strcpy(p[i].left,token1);
        strcpy(p[i].right,token2);
    }
    printf("Enter the input\n");
    scanf("%s",input);
    ch[0]='\0';
    stack[0]='\0';
    while(1)
    {
        if(i<strlen(input))
        {
             ch[0]=input[i];
             ch[1]='\0';
             i++;
             strcat(stack,ch);
               printf("stack:%s   ",stack);
           printf("input:");
           for(int k=i;k<strlen(input);k++)
           {
               printf("%c",input[k]);
           }
           printf("   ");
           printf("shift");
           printf("\n");
        }
        for(j=0;j<rule;j++)
        {
            sub=strstr(stack,p[j].right);
            if(sub!=NULL)
            {
                subl=strlen(p[j].right);
                sl=strlen(stack);
                top=sl-subl;
                stack[top]='\0';
                strcat(stack,p[j].left);
                printf("stack:%s   ",stack);
           printf("input:");
           for(int k=i;k<strlen(input);k++)
           {
               printf("%c",input[k]);
           }
           printf("   ");
           printf("Reduce %s->%s",p[j].left,p[j].right);
           printf("\n");
            j=-1;
            }
           
        }
        if(strcmp(stack,p[0].left)==0 && i==strlen(input))
        {
            printf("Parsing sucessfull\n");
            break;
        }
        else if(i==strlen(input))
        {
             printf("Parsing Not sucessfull\n");
            break;
        }
        
    }
}
