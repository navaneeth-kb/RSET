#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int staddr1, i, j;
    char line[50], staddr[10], userProgName[10], fileProgName[10];

    // Prompt the user for the program name
    printf("Enter the program name: ");
    scanf("%s", userProgName);

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;  // Return non-zero for error
    }

    // Read the header
    fscanf(fp, "%s", line);
    sscanf(line, "H^%6s^%*s", fileProgName);
    
    // Verify the program name
    if (strcmp(userProgName, fileProgName) != 0) {
        printf("Program name mismatch. Expected: %s, Found: %s\n", userProgName, fileProgName);
        fclose(fp);
        return 1;  // Return non-zero for error
    }

    while (!feof(fp)) {
        fscanf(fp, "%s", line); // Read the next line
        if (line[0] == 'T') {
            sscanf(line, "T^%6s^%*s", staddr);   // Extract the starting address
            staddr1 = (int)strtol(staddr, NULL, 16);  // Convert to integer
            i = 12;  // Start after the address and length fields

            while (i < strlen(line) && line[i] != '$') {
                if (line[i] != '^') { // Skip the '^'
                    printf("%04X\t", staddr1); // Print the starting address
                    for (j = 0; j < 6 && line[i + j] != '\0' && line[i + j] != '^' && line[i + j] != '$'; j++) {
                        printf("%c", line[i + j]); // Print each character of the object code
                    }
                    printf("\n"); // Newline after each object code segment
                    staddr1 += 3; // Increment address by 3
                    i += j; // Move to the next object code segment
                } else {
                    i++;
                }
            }
        }
    }

    fclose(fp);
    return 0;  // Return 0 for successful execution
}
