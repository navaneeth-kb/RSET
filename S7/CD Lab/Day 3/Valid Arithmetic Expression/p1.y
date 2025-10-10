%{
  #include <stdio.h>
  #include <stdlib.h>
  int yylex();
  void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS

%%

expression:
expression '+' expression
| expression '-' expression
| expression '*' expression
| expression '/' expression
| '-' expression %prec UMINUS
| '(' expression ')'
| NUMBER
;

%%

void yyerror(const char *s) {
printf("Error: %s\n", s);
}

int main() {
  printf("Enter an arithmetic expression:\n");
  if (yyparse() == 0)
    printf("Valid arithmetic expression.\n");
  else
    printf("Invalid arithmetic expression.\n");
  return 0;
}
