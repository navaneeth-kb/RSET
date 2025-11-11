#include<stdio.h>
#include <stdlib.h>
#include <string.h>

char *keywords[]=  {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof",
"static","struct","switch","typedef","union","unsigned","void","volatile","while"};

int isKeyword(char *key)
{
    for (int i=0;i<(sizeof(keywords)/sizeof(keywords[0]));i++)
    {
        if (strcmp(keywords[i],key)==0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    FILE *fp=fopen("test.txt","r");
    char ch,buffer[100];

    if (!fp)
    {
        printf("Cant open file");
        return 0;
    }

    while ((ch=fgetc(fp))!=EOF)
    {
        if (isspace(ch))
        {
            continue;
        }

        switch(ch)
        {
            case '=':
            case '>':
            case '<':
            case '!':
            {
                buffer[0]=ch;
                buffer[1]=fgetc(fp);
                if (buffer[1]=='=')
                {
                    buffer[2]='\0';
                }
                else
                {
                    ungetc(buffer[1],fp);
                    buffer[1]='\0';
                }
                printf("Relational operator: %s\n",buffer);
                break;
            }

            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            {
                buffer[0]=ch;
                buffer[1]=fgetc(fp);
                buffer[2]='\0';
                if (buffer[0]=='/' && buffer[1]=='/')
                {
                    while((ch=fgetc(fp))!='\n' && ch!=EOF)
                        ;
                }
                else if (buffer[0]=='/' && buffer[1]=='*')
                {
                    while((ch=fgetc(fp))!=EOF)
                    {
                        if (ch=='*' && fgetc(fp)=='/')
                        {
                            break;
                        }
                    }
                }
                else
                {
                    ungetc(buffer[1],fp);
                    ungetc(buffer[2],fp);
                    buffer[1]='\0';
                    printf("Arithmetic operator: %c\n",ch);
                }
                break;
            }

            case '#':
            {
                while((ch=fgetc(fp))!='\n' && ch!=EOF)
                    ;
                break;
            }

            default:
            {
                if (isalpha(ch) || ch=='_')
                {
                    int i=0;
                    do
                    {
                        buffer[i++]=ch;
                    }
                    while ((isalnum(ch=fgetc(fp))) || ch=='_');
                    buffer[i]='\0';
                    ungetc(ch,fp);
                    if (isKeyword(buffer))
                    {
                        printf("Keyword: %s\n",buffer);
                    }
                    else
                    {
                        printf("Identifier: %s\n",buffer);
                    }
                }
                if (isdigit(ch))
                {
                    int i=0;
                    do
                    {
                        buffer[i++]=ch;
                    }
                    while (isdigit(ch=fgetc(fp)));
                    buffer[i]='\0';
                    ungetc(ch,fp);
                    printf("Digit: %s\n",buffer);
                }
                break;
            }
        }
    }

    fclose(fp);
    return 0;
}
