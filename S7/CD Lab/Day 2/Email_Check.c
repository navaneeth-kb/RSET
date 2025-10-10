%{
#include <stdio.h>

int valid_email_count = 0;
%}

%%
[a-zA-Z0-9._%]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,} {
    printf("Valid Email: %s\n", yytext);
    valid_email_count++;
}
.|\n  { /* Ignore all other characters */ }
%%

int main() {
    yylex();
    printf("Total valid emails found: %d\n", valid_email_count);
    return 0;
}

int yywrap() {
    return 1;
}
