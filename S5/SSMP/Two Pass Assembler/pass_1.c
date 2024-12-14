#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void close_files(FILE *input_ptr, FILE *symtab_ptr, FILE *intermed_ptr, FILE *length_ptr) {
    fclose(input_ptr);
    fclose(symtab_ptr);
    fclose(intermed_ptr);
    fclose(length_ptr);
}

int is_duplicate_label(char symtab[][10], int symtab_count, char *label) {
    for (int i = 0; i < symtab_count; i++) {
        if (strcmp(label, symtab[i]) == 0) {
            printf("Error: Duplicate label found: %s\n", label);
            return 1;
        }
    }
    return 0;
}

int find_opcode_length(FILE *optab_ptr, char *opcode) {
    char opc[20], value[10];
    rewind(optab_ptr); // Reset the file pointer to the beginning
    while (fscanf(optab_ptr, "%s %s", opc, value) != EOF) {
        char temp[20] = "+";
        strcat(temp, opc);
        if (strcmp(opcode, opc) == 0 || strcmp(opcode, temp) == 0)
            return opcode[0] == '+' ? 4 : 3;
    }
    printf("Invalid opcode: %s\n", opcode);
    return -1; // Return -1 for invalid opcode
}

int main() {
    int start_addr, locctr, length = 0, end_found = 0;
    char label[20], opcode[20], operand[20];
    char symtab[100][10];
    int symtab_count = 0;

    FILE *input_ptr = fopen("input.txt", "r");
    FILE *optab_ptr = fopen("optab.txt", "r");
    FILE *symtab_ptr = fopen("symtab.txt", "w");
    FILE *intermed_ptr = fopen("intermediate.txt", "w");
    FILE *length_ptr = fopen("length.txt", "w");

    while (fscanf(input_ptr, "%s %s %s", label, opcode, operand) != EOF) {
        if (strcmp(opcode, "START") == 0) {
            start_addr = (int)strtol(operand, NULL, 16);
            locctr = start_addr;
            fprintf(intermed_ptr, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
            continue;
        }

        if (strcmp(opcode, "END") == 0) {
            if (!end_found) {
                fprintf(intermed_ptr, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
                end_found = 1;
            }
            break; // Break the loop after END is encountered
        }

        // Check for duplicate label and insert into SYMTAB
        if (strcmp(label, "-") != 0 && !is_duplicate_label(symtab, symtab_count, label)) {
            strcpy(symtab[symtab_count++], label);
            fprintf(symtab_ptr, "%s\t%X\n", label, locctr);
        }

        // Calculate length based on opcode
        if (strcmp(opcode, "BYTE") == 0) {
            length = strlen(operand) - 3;
        } else if (strcmp(opcode, "WORD") == 0) {
            length = 3;
        } else if (strcmp(opcode, "RESB") == 0) {
            length = (int)strtol(operand, NULL, 16);
        } else if (strcmp(opcode, "RESW") == 0) {
            length = 3 * (int)strtol(operand, NULL, 16);
        } else {
            length = find_opcode_length(optab_ptr, opcode);
            if (length == -1) continue; // Skip invalid opcode
        }

        fprintf(intermed_ptr, "%X\t%d\t%s\t%s\t%s\n", locctr, length, label, opcode, operand);
        locctr += length;
    }

    fprintf(length_ptr, "%X\n", locctr - start_addr);
    close_files(input_ptr, symtab_ptr, intermed_ptr, length_ptr);

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

    fclose(optab_ptr);
    return 0;
}
