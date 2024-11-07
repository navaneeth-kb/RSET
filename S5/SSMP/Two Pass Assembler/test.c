#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *searchOptab(char *mnemonic)
{
    static char opcode[10];
    FILE *optab = fopen("Optab.txt", "r");
    if (!optab)
    {
        printf("Error opening Optab.txt\n");
        exit(1);
    }

    char op[10], code[10];
    while (fscanf(optab, "%s %s", op, code) != EOF)
        if (strcmp(op, mnemonic) == 0)
        {
            fclose(optab);
            return strcpy(opcode, code);
        }

    fclose(optab);
    return NULL;
}

int searchSymtab(char *label)
{
    FILE *symtab = fopen("SYMTAB.txt", "r");
    if (!symtab) return -1;

    char sym[20];
    int address;
    while (fscanf(symtab, "%s %X", sym, &address) != EOF)
        if (strcmp(sym, label) == 0)
        {
            fclose(symtab);
            return address;
        }

    fclose(symtab);
    return -1;
}

int main()
{
    FILE *intermediate = fopen("Intermediate.txt", "r"), *objectCode = fopen("ObjectCode.txt", "w"), *lengthFile = fopen("Length.txt", "r");
    if (!intermediate || !objectCode || !lengthFile)
    {
        printf("Error opening files\n");
        exit(1);
    }

    char label[20], opcode[20], operand[20], objectCodeBuffer[100] = "";
    int locctr, startAddress, address, programLength, textRecordLength = 0, maxTextRecordLength = 9, textRecordStart;
    fscanf(lengthFile, "Program length: %X", &programLength);
    fclose(lengthFile);

    fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        startAddress = locctr;
        fprintf(objectCode, "H^%s^%06X^%06X\n", label, startAddress, programLength);
    }
    textRecordStart = locctr;

    while (fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand) != EOF)
    {
        if (strcmp(opcode, "END") == 0)
        {
            if (textRecordLength > 0)
                fprintf(objectCode, "T^%06X^%02X^%s\n", textRecordStart, textRecordLength, objectCodeBuffer);
            fprintf(objectCode, "E^%06X\n", startAddress);
            break;
        }

        char currentObjectCode[20] = "";
        char *op = searchOptab(opcode);
        if (op)
        {
            address = searchSymtab(operand);
            sprintf(currentObjectCode, "%s%04X", op, (address != -1) ? address : 0);
        }
        else if (strcmp(opcode, "WORD") == 0)
            sprintf(currentObjectCode, "%06X", atoi(operand));
        else if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'C')
                for (int i = 2; i < strlen(operand) - 1; i++)
                    sprintf(currentObjectCode + strlen(currentObjectCode), "%02X", operand[i]);
            else if (operand[0] == 'X')
                strncpy(currentObjectCode, operand + 2, strlen(operand) - 3);
        }

        int objectCodeLength = strlen(currentObjectCode) / 2;
        if (textRecordLength + objectCodeLength > maxTextRecordLength)
        {
            fprintf(objectCode, "T^%06X^%02X^%s\n", textRecordStart, textRecordLength, objectCodeBuffer);
            strcpy(objectCodeBuffer, "");
            textRecordLength = 0;
            textRecordStart = locctr;
        }
        if (textRecordLength > 0) strcat(objectCodeBuffer, "^");
        strcat(objectCodeBuffer, currentObjectCode);
        textRecordLength += objectCodeLength;
    }

    fclose(intermediate);
    fclose(objectCode);

    printf("Pass 2 completed. Object program generated in ObjectCode.txt.\n");
    return 0;
}