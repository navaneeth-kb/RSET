%{
#include <stdio.h>

int line_count = 0;
int word_count = 0;
int char_count = 0;
%}

%%
\n              { line_count++; char_count++; }
[ \t]+          { char_count += yyleng; } // Skip whitespace but count characters
[a-zA-Z]+        { word_count++; char_count += yyleng; } // Count words and chars
.               { char_count++; } // For any other character
%%

int main(int argc, char **argv) {
    yylex();
    printf("Lines: %d\n", line_count);
    printf("Words: %d\n", word_count);
    printf("Characters: %d\n", char_count);
    return 0;
}

int yywrap() {
    return 1;
}
