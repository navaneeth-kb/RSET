#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof",
"static","struct","switch","typedef","union","unsigned","void","volatile","while"};

int isKeyword(char *str)
{
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;
	    return 0;
}

int main()
{
    FILE *fp = fopen("input.c", "r");
    char ch, buffer[100];
    int i;
    if (!fp)
    {
        printf("Cannot open file\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch))
            continue;

        switch (ch)
        {
        case '=':
        case '>':
        case '<':
        case '!':
            buffer[0] = ch;
            buffer[1] = fgetc(fp);
            if (buffer[1] == '=')
                buffer[2] = '\0';
            else
            {
                ungetc(buffer[1], fp);
                buffer[1] = '\0';
            }
            printf("Relational Operator: %s\n", buffer);
            break;

        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            buffer[0] = ch;
            buffer[1] = '\0';
            if (ch == '/' && (buffer[1] = fgetc(fp)) == '/')
            {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF)
                    ;
            }
            else if (ch == '/' && buffer[1] == '*')
            {
                while ((ch = fgetc(fp)) != EOF)
                    if (ch == '*' && fgetc(fp) == '/')
                        break;
            }
            else
            {
                if (buffer[1])
                    ungetc(buffer[1], fp);
                printf("Arithmetic Operator: %c\n", ch);
            }
            break;

        case '#':
            while ((ch = fgetc(fp)) != '\n' && ch != EOF)
                ;
            break;

        default:
            if (isalpha(ch) || ch == '_')
            {
                i = 0;
                do
                    buffer[i++] = ch;
                while (isalnum(ch = fgetc(fp)) || ch == '_');
                buffer[i] = '\0';
                ungetc(ch, fp);
                if (isKeyword(buffer))
                    printf("Keyword: %s\n", buffer);
                else
                    printf("Identifier: %s\n", buffer);
            }
            else if (isdigit(ch))
            {
                i = 0;
                do
                    buffer[i++] = ch;
                while (isdigit(ch = fgetc(fp)));
                buffer[i] = '\0';
                ungetc(ch, fp);
                printf("Number: %s\n", buffer);
            }
            break;
        }
    }

    fclose(fp);
    return 0;
}
