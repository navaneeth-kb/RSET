#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
    int start_addr;
    int locctr;
    int length;
    int end_found = 0; // Flag to indicate if END has been processed
   
    char label[20];
    char opcode[20];
    char operand[20];

    char symtab[100][10];
    int symtab_count = 0;
   
    FILE *input_ptr, *optab_ptr, *symtab_ptr, *intermed_ptr, *length_ptr;
   
    input_ptr = fopen("input.txt", "r");
    symtab_ptr = fopen("symtab.txt", "w");
    intermed_ptr = fopen("intermediate.txt", "w");
    length_ptr = fopen("length.txt", "w");

    while (feof(input_ptr) == 0)
    {  
        fscanf(input_ptr, "%s %s %s", label, opcode, operand);

        if (strcmp(label, "-") != 0 && strcmp(opcode, "START") != 0 && strcmp(opcode, "END") != 0)
        {
            //while (strcmp(opcode, "END") != 0) {
            int is_duplicate_label = 0;  

            if (strcmp(label, "-") != 0 && strcmp(label, "") != 0) {
             for (int i = 0; i < symtab_count; i++) {
                if (strcmp(label, symtab[i]) == 0) {
                    printf("Error: Duplicate label found: %s\n", label);
                    is_duplicate_label = 1;
                    exit(0);
                    break;
                }
            }

            }if (!is_duplicate_label) {
                strcpy(symtab[symtab_count++], label);
                fprintf(symtab_ptr, "%s\t%X\n", label, locctr); // Store in hex
            }
        }

            //fprintf(symtab_ptr, "%s\t%X\n", label, locctr);
        //}

        if (strcmp(opcode, "START") == 0)
        {
            length = 0;
            start_addr = (int)strtol(operand, NULL, 16);
            locctr = start_addr;
        }
        else if (strcmp(opcode, "END") == 0)
        {
            if (!end_found) {
                fprintf(intermed_ptr, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand); // Print END once
               
                end_found = 1; // Mark END as found
            }
            continue; // Skip further processing for this iteration
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'X')
                length = (strlen(operand) - 3) / 2;
            else if (operand[0] == 'C')
                length = strlen(operand) - 5;
        }
        else if (strcmp(opcode, "WORD") == 0)
            length = 3;
        else if (strcmp(opcode, "RESB") == 0)
            length = (int)strtol(operand, NULL, 16);
        else if (strcmp(opcode, "RESW") == 0)
            length = 3 * (int)strtol(operand, NULL, 16);
        else
        {
            if (opcode[0] == '+')
                length = 4;
            else
                length = 3;

            char opc[20];
            char value[10];
            int flag = 0;            

            optab_ptr = fopen("optab.txt", "r");
            while (feof(optab_ptr) == 0)
            {
                fscanf(optab_ptr, "%s %s", opc, value);
                char temp[20] = "+";
                strcat(temp, opc);

                if (strcmp(opcode, opc) == 0 || strcmp(opcode, temp) == 0)
                {
                    flag = 1;
                    break;
                }  
            }
            fclose(optab_ptr);

            if (flag == 0)
            {
                printf("Invalid opcode: %s\n", opcode);
                continue; // Skip to the next line
            }
        }      

        fprintf(intermed_ptr, "%X\t%d\t%s\t%s\t%s\n", locctr, length, label, opcode, operand);
     
        locctr += length;
    }

    fprintf(length_ptr, "%X\n", locctr - start_addr);

    fclose(input_ptr);
    fclose(symtab_ptr);
    fclose(intermed_ptr);
    fclose(length_ptr);
    
    

    // Display INTERMEDIATE file contents
    printf("\n====INTERMEDIATE====\n");
    intermed_ptr = fopen("intermediate.txt", "r");
    char inter_line[100];
    while (fgets(inter_line, sizeof(inter_line), intermed_ptr) != NULL) {
        printf("%s", inter_line);
    }
    fclose(intermed_ptr);

    // Calculate and display program length
    length = locctr - start_addr;
    printf("\n====LENGTH====\n");
    printf("Program length: %X\n", length);
}
