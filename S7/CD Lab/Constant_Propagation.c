#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

struct Instruction {
    char lhs[10], op1[10], op[5], op2[10];
} code[MAX];

int n;

int isConstant(char *s) {
    for (int i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

int main() {
    printf("Enter number of instructions > ");
    scanf("%d", &n);

    printf("Enter the three-address:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s = %s %s %s", code[i].lhs, code[i].op1, code[i].op, code[i].op2);
    }

    // Perform constant propagation
    for (int i = 0; i < n; i++) {
        if (isConstant(code[i].op1) && isConstant(code[i].op2)) {
            int val1 = atoi(code[i].op1);
            int val2 = atoi(code[i].op2);
            int result = 0;

            if (strcmp(code[i].op, "+") == 0) result = val1 + val2;
            else if (strcmp(code[i].op, "-") == 0) result = val1 - val2;
            else if (strcmp(code[i].op, "*") == 0) result = val1 * val2;
            else if (strcmp(code[i].op, "/") == 0 && val2 != 0) result = val1 / val2;

            sprintf(code[i].op1, "%d", result);
            strcpy(code[i].op, "");
            strcpy(code[i].op2, "");
        }

        // Propagate constants forward
        for (int j = i + 1; j < n; j++) {
            if (strcmp(code[j].op1, code[i].lhs) == 0 && isConstant(code[i].op1)) {
                strcpy(code[j].op1, code[i].op1);
            }
            if (strcmp(code[j].op2, code[i].lhs) == 0 && isConstant(code[i].op1)) {
                strcpy(code[j].op2, code[i].op1);
            }
        }
    }

    printf("\nOptimized Code:\n");
    for (int i = 0; i < n; i++) {
        if (strlen(code[i].op) == 0)
            printf("%s = %s\n", code[i].lhs, code[i].op1);
        else
            printf("%s = %s %s %s\n", code[i].lhs, code[i].op1, code[i].op, code[i].op2);
    }

    return 0;
}
