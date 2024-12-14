#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char code[20];
char *searchoptab(char *opc)
{
    FILE *optab_ptr=fopen("optab.txt","r");
    if (optab_ptr == NULL)
    {
        printf("Error opening Optab.txt\n");
        exit(1);
    }
    char opcode[20];

    while((fscanf(optab_ptr,"%s %s",opcode,code))!=EOF)
    {
        if ((strcmp(opcode,opc)==0))
        {
            fclose(optab_ptr);
            return code;
        }
    }
    return NULL;
    fclose(optab_ptr);
}

int adr;
int searchsymtab(char *op)
{
    FILE *symtab_ptr=fopen("symtab.txt","r");
    if (symtab_ptr == NULL)
    {
        printf("Error opening symtab.txt\n");
        exit(1);
    }
    char opr[20];

    while((fscanf(symtab_ptr,"%s %X",opr,&adr))!=EOF)
    {
        if ((strcmp(opr,op)==0))
        {
            fclose(symtab_ptr);
            return adr;
        }
    }
    return -1;
    fclose(symtab_ptr);
}

void main()
{
    FILE *intermediate_ptr=fopen("intermediate.txt","r");
    FILE *length_ptr=fopen("length.txt","r");
    FILE *objectcode_ptr=fopen("objectcode.txt","w");

    int locctr,start_adr,length;
    char label[20],opcode[20],operand[20];

    fscanf(length_ptr,"Program length is %X",&length);
    fscanf(intermediate_ptr,"%X %s %s %s",&locctr,label,opcode,operand);
    if (strcmp(opcode,"START")==0)
    {
        start_adr=locctr;
        fprintf(objectcode_ptr,"H^%s^%06X^%06X\n",label,locctr,length);
    }

    char objectcodebuffer[100]="";
    int textrecordstart=start_adr;
    int textrecordlength=0;

    while((fscanf(intermediate_ptr,"%X %s %s %s",&locctr,label,opcode,operand))!=EOF)
    {
        if(strcmp(opcode,"END")==0)
        {
            if(textrecordlength>0)
            {
                fprintf(objectcode_ptr,"T^%06X^%02X^%s\n",textrecordstart,textrecordlength,objectcodebuffer);
            }
            fprintf(objectcode_ptr,"E^%06X\n",start_adr);
        }

        char currentobjectcode[50]="";
        int address;

        char *op=searchoptab(opcode);
        if(op!=NULL)
        {
            address=searchsymtab(operand);
            if (address!=-1)
            {
                sprintf(currentobjectcode,"%02s%04X",op,address);
            }
            else if((strcmp(operand,"-"))==0)
            {
                sprintf(currentobjectcode,"%02s%0000",op);
            }
        }
        else if((strcmp(opcode,"WORD"))==0)
        {
            int value=atoi(operand);
            sprintf(currentobjectcode,"%06X",value);
        }
        else if((strcmp(opcode,"BYTE"))==0)
        {
            if (operand[0]=='C')
            {
                for (int i=2;i<strlen(operand)-3;i++)
                {
                    char hexval[3];
                    sprintf(hexval,"%02X",operand[i]);
                    strcat(currentobjectcode,hexval);
                }
            }
            else if(operand[0]=='X')
            {
                strncpy(currentobjectcode,operand+2,strlen(operand)-3);
                currentobjectcode[strlen(operand)-3]='\0';
            }
        }

        int objectcodelength=(strlen(currentobjectcode))/2;

        int num=0;
        if(objectcodelength+textrecordlength > 9)
        {
            fprintf(objectcode_ptr,"T^%06X^%02X^%s\n",textrecordstart,textrecordlength,objectcodebuffer);
            strcpy(objectcodebuffer,"");
            textrecordstart=locctr;
            textrecordlength=0;
            num=1;
        }

        if(textrecordlength>0 && num!=1)
        {
            strcat(objectcodebuffer,"^");
        }
        strcat(objectcodebuffer, currentobjectcode);
        textrecordlength += objectcodelength;
    }

    fclose(intermediate_ptr);
    fclose(objectcode_ptr);

    printf("Pass 2 completed. Object program generated in ObjectCode.txt.\n");
}
