%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token IDENTIFIER

%%

input:
/* empty */
| input line ;
line:
IDENTIFIER '\n' { printf("Valid identifier\n"); }
| error '\n' { printf("Invalid identifier\n"); yyerrok; } ;

%%

void yyerror(const char *s) {
}

int main() {
  printf("Enter identifiers (Crtl+D to stop) :\n");
  yyparse();
  return 0;
}
