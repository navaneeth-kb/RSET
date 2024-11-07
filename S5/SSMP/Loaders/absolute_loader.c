#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char col1[10], filename[10], startloc[10], length[10], strtadr[10], objcd[10], strtemp[10];
    int i, j, adr[10], obj[10], inttemp, adrctr;
    FILE *fp;

    fp = fopen("objectcode_1.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(fp, "%s %s %s %s", col1, filename, startloc, length);
    fscanf(fp, "%s", col1);
    i = 0;

    while (strcmp(col1, "T") == 0) {
        if (fscanf(fp, "%s %s %s", strtadr, length, objcd) != 3) {
            printf("Error reading input line\n");
            exit(1);
        }

        adrctr = atoi(strtadr);

        while (strcmp(objcd, "T") != 0) {
            if (strcmp(objcd, "E") == 0) {
                break;
            }

            inttemp = atoi(objcd);
            obj[i + 2] = inttemp % 100;
            inttemp = inttemp / 100;
            obj[i + 1] = inttemp % 100;
            inttemp = inttemp / 100;
            obj[i] = inttemp % 100;
            inttemp = inttemp / 100;

            adr[i++] = adrctr++;
            adr[i++] = adrctr++;
            adr[i++] = adrctr++;

            fscanf(fp, "%s", objcd);
        }

        strcpy(col1, objcd);
    }

    printf("Addresses\tObject Codes\n");
    for (j = 0; j < i; j++) {
        printf("00%d\t\t", adr[j]);
        if (obj[j] < 10) {
            printf("0");
        }
        printf("%d\n", obj[j]);
    }

    fclose(fp);
}