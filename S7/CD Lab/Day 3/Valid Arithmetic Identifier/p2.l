%{
#include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]* { return IDENTIFIER; }
[ \t]+ ; // Skip whitespace
\n { return '\n'; }
. { return yytext[0]; } // Any invalid char

%%

int yywrap() {
	return 1;
}
