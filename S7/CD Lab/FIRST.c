#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 
 
#define MAX 20 
 
char productions[MAX][MAX];   // Grammar productions 
char firstSets[MAX][MAX];     // Store FIRST sets 
int n;                        // Number of productions 
 
 
void findFirst(char[], char); 
void addToFirst(char[], char); 
 
int main() { 
    int i; 
    char choice; 
 
    printf("Enter number of productions: "); 
    scanf("%d", &n); 
 
    printf("Enter the productions (like E=E+T or T=i):\n"); 
    for (i = 0; i < n; i++) { 
        scanf("%s", productions[i]); 
    } 
 
    // Compute FIRST for each non-terminal 
    int visited[256] = {0};   // Mark non-terminals we have printed 
 
 for (i = 0; i < n; i++) { 
     char nonTerminal = productions[i][0]; 
 
     if (!visited[(int)nonTerminal]) { 
  char result[MAX]; 
  result[0] = '\0'; 
 
  findFirst(result, nonTerminal); 
 
  printf("FIRST(%c) = { ", nonTerminal); 
  for (int j = 0; result[j] != '\0'; j++) { 
      printf("%c ", result[j]); 
  } 
  printf("}\n"); 
 
  visited[(int)nonTerminal] = 1;  // Mark as printed 
     } 
 } 
 
 
    return 0; 
} 
 
 
void findFirst(char result[], char symbol) { 
    int i, j, k; 
 
    // If symbol is a terminal, add it to result 
    if (!isupper(symbol)) { 
        addToFirst(result, symbol); 
        return; 
    } 
 
    // Check all productions with LHS = symbol 
    for (i = 0; i < n; i++) { 
        if (productions[i][0] == symbol) { 
            // If RHS is epsilon 
            if (productions[i][2] == '#') {  // Assume # as epsilon 
                addToFirst(result, '#'); 
            }  
            else { 
                // For each symbol in RHS 
                for (j = 2; j < strlen(productions[i]); j++) { 
                    char nextSym = productions[i][j]; 
 
                    // If terminal, add it 
                    if (!isupper(nextSym)) { 
                        addToFirst(result, nextSym); 
                        break; 
                    }  
                    else { 
                        // If non-terminal, compute FIRST recursively 
                        char temp[MAX]; 
                        temp[0] = '\0'; 
                        findFirst(temp, nextSym); 
 
                        for (k = 0; temp[k] != '\0'; k++) { 
                            if (temp[k] != '#') { 
                                addToFirst(result, temp[k]); 
                            } else { 
                                // If epsilon, check next symbol 
                                if (productions[i][j+1] == '\0') {   
//if # is last symbol in RHS 
                                    addToFirst(result, '#'); 
                                } 
                                continue; 
                            } 
                        } 
 
                        // If epsilon not in FIRST, stop 
                        if (strchr(temp, '#') == NULL) { 
                            break; 
                        } 
                    } 
                } 
            } 
        } 
    } 
} 
// Add unique symbols to FIRST set 
void addToFirst(char result[], char symbol) { 
    if (strchr(result, symbol) == NULL) { 
        int len = strlen(result); 
        result[len] = symbol; 
        result[len+1] = '\0'; 
    } 
}
