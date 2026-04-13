%{
#include "q2_if.tab.h"
%}

%%

"if"        { return IF; }
"else"      { return ELSE; }
[0-9]+      { return NUM; }
[a-zA-Z]+   { return ID; }
\n          { return NL; }
[ \t]       ;
.           { return yytext[0]; }

%%

int yywrap(){ return 1; }
