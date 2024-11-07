#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *searchOptab(char *mnemonic)
{
    FILE *optab;
    static char opcode[10];
    char op[10], code[10];

    optab = fopen("Optab.txt", "r");
    if (optab == NULL)
    {
        printf("Error opening Optab.txt\n");
        exit(1);
    }

    while (fscanf(optab, "%s %s", op, code) != EOF)
    {
        if (strcmp(op, mnemonic) == 0)
        {
            strcpy(opcode, code);
            fclose(optab);
            return opcode;
        }
    }

    fclose(optab);
    return NULL;
}

int searchSymtab(char *label)
{
    FILE *symtab;
    char sym[20];
    int address;

    symtab = fopen("SYMTAB.txt", "r");
    if (symtab == NULL)
    {
        return -1;
    }
    while (fscanf(symtab, "%s %X", sym, &address) != EOF)
    {
        if (strcmp(sym, label) == 0)
        {
            fclose(symtab);
            return address; // Label found
        }
    }

    fclose(symtab);
    return -1; // Label not found
}

int main()
{
    FILE *intermediate, *objectCode, *lengthFile;
    char label[20], opcode[20], operand[20], objectCodeBuffer[100];
    int locctr, startAddress, address, programLength, objectCodeLength;
    char *op;
    int textRecordLength = 0;
    int maxTextRecordLength = 9;

    intermediate = fopen("Intermediate.txt", "r");
    objectCode = fopen("ObjectCode.txt", "w");
    lengthFile = fopen("Length.txt", "r");

    if (intermediate == NULL || objectCode == NULL || lengthFile == NULL)
    {
        printf("Error opening files\n");
        exit(1);
    }

    fscanf(lengthFile, "Program length: %X", &programLength);
    fclose(lengthFile);

    fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        startAddress = locctr;                                                       // Store the start address for the END record
        fprintf(objectCode, "H^%s^%06X^%06X\n", label, startAddress, programLength); // Header record
    }

    objectCodeBuffer[0] = '\0';
    textRecordLength = 0;
    int textRecordStart = locctr;

    while (fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand) != EOF)
    {
        // Handle the 'END' directive
        if (strcmp(opcode, "END") == 0)
        {
            if (textRecordLength > 0)
            {
                fprintf(objectCode, "T^%06X^%02X^%s\n", textRecordStart, textRecordLength, objectCodeBuffer);
            }
            fprintf(objectCode, "E^%06X\n", startAddress); // End record
            break;
        }

        char currentObjectCode[20] = "";

        op = searchOptab(opcode);
        if (op != NULL)
        {

            address = searchSymtab(operand);
            if (address != -1)
            {
                // object code (opcode + address)
                sprintf(currentObjectCode, "%s%04X", op, address);
            }
            else if (strcmp(operand, "-") == 0)
            {
                // Instruction RSUB
                sprintf(currentObjectCode, "%s0000", op);
            }
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            int value = atoi(operand);
            sprintf(currentObjectCode, "%06X", value); // WORD is 3 bytes
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'C')
            {
                // BYTE C'...'
                for (int i = 2; i < strlen(operand) - 1; i++)
                {
                    char hexValue[3];
                    sprintf(hexValue, "%02X", (unsigned char)operand[i]);
                    strcat(currentObjectCode, hexValue);
                }
            }
            else if (operand[0] == 'X')
            {
                // BYTE X'...'
                strncpy(currentObjectCode, operand + 2, strlen(operand) - 3); // Extract the hex value
                currentObjectCode[strlen(operand) - 3] = '\0';
            }
        }
        objectCodeLength = strlen(currentObjectCode) / 2;
        int new;
        if (textRecordLength + objectCodeLength > maxTextRecordLength)
        {
            fprintf(objectCode, "T^%06X^%02X^%s\n", textRecordStart, textRecordLength, objectCodeBuffer);
            // Start a new text record
            strcpy(objectCodeBuffer, ""); // Reset buffer
            textRecordLength = 0;
            textRecordStart = locctr;
            new = 1;
        }
        if (textRecordLength > 0 && new != 1)
        {
            strcat(objectCodeBuffer, "^"); // Add separator before appending the next object code
        }
        strcat(objectCodeBuffer, currentObjectCode);
        textRecordLength += objectCodeLength;
    }

    fclose(intermediate);
    fclose(objectCode);

    printf("Pass 2 completed. Object program generated in ObjectCode.txt.\n");

    return 0;
}