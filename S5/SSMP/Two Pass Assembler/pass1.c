#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_opcode_length(FILE *optab_ptr, char *opcode)
{
    rewind(optab_ptr);
    char opc[40];
    int opv;
    while(fscanf(optab_ptr,"%s %X",opc,&opv)!=EOF)
    {
        if(strcmp(opc,opcode)==0)
        {
            return 3;
        }
    }
    return -1;
}

int duplicate_label(char symtab[][10], int symtab_count, char *label) {
    for (int i = 0; i < symtab_count; i++) {
        if (strcmp(label, symtab[i]) == 0) {
            printf("Error: Duplicate label found: %s\n", label);
            return 1;
        }
    }
    return 0;
}

void main()
{
    char label[20]="", opcode[20]="", operand[20]="";
    int start_adr=0, locctr=0, length = 0;
    char symtab[100][10];
    int symtab_count = 0;

    FILE *input_ptr=fopen("input.txt","r");
    FILE *optab_ptr=fopen("optab.txt","r");
    FILE *intermediate_ptr=fopen("intermediate.txt","w");
    FILE *symtab_ptr=fopen("symtab.txt","w");
    FILE *length_ptr=fopen("length.txt","w");

    if (!input_ptr || !optab_ptr || !intermediate_ptr || !symtab_ptr || !length_ptr) {
        printf("Error: Could not open one or more files.\n");
        exit(1);
    }

    while(fscanf(input_ptr,"%s %s %s",label,opcode,operand)!=EOF)
    {
        if(strcmp(opcode,"START")==0)
        {
            start_adr=(int)strtol(operand,NULL,16);
            locctr=start_adr;
            fprintf(intermediate_ptr,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
            continue;
        }

        if(strcmp(opcode,"END")==0)
        {
            fprintf(intermediate_ptr,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
            break;
        }

        if((strcmp(label,"-")!=0) && (!duplicate_label(symtab,symtab_count,label)))
        {
            strcpy(symtab[symtab_count++], label);
            fprintf(symtab_ptr, "%s\t%X\n", label, locctr);
        }

        if(strcmp(opcode,"BYTE")==0)
        {
            length=strlen(operand)-3;
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            length=3;
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            length=(int)strtol(operand,NULL,16);
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            length=3*((int)strtol(operand,NULL,16));
        }
        else
        {
            length=find_opcode_length(optab_ptr,opcode);
            if (length==-1)
            {
                printf("Error: Invalid opcode %s\n", opcode);
                continue;
            }
        }
        fprintf(intermediate_ptr,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        locctr+=length;
    }

    fprintf(length_ptr,"Program length is %X\n",locctr-start_adr);

    fclose(input_ptr);
    fclose(symtab_ptr);
    fclose(intermediate_ptr);
    fclose(length_ptr);

    printf("\n====INTERMEDIATE====\n");
    intermediate_ptr = fopen("intermediate.txt", "r");
    char inter_line[100];
    while(fgets(inter_line,sizeof(inter_line),intermediate_ptr)!=NULL)
    {
        printf("%s", inter_line);
    }
    fclose(intermediate_ptr);

    length = locctr - start_adr;
    printf("\n====LENGTH====\n");
    printf("Program length: %X\n", length);
}
