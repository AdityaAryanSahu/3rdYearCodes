%{
#include "q1_decl.tab.h"
%}

%%

"int"|"float"|"char"    { return TYPE; }
[a-zA-Z][a-zA-Z0-9_]*   { return ID; }
";"                     { return ';'; }
\n                      { return NL; }
[ \t]                   ;
.                       { return yytext[0]; }

%%

int yywrap(){ return 1; }
