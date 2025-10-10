%{
#include <stdio.h>

int vowels = 0;
int consonants = 0;
%}

%%
[aAeEiIoOuU]     { vowels++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { consonants++; }
.|\n             { /* Ignore other characters */ }
%%

int main() {
    yylex();
    printf("Total vowels: %d\n", vowels);
    printf("Total consonants: %d\n", consonants);
    return 0;
}

int yywrap() {
    return 1;
}
