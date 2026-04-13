%{
#include "q.tab.h"

%}

%%

"main" {return MAIN;}
"int"|"char" {return TYPE;}
[a-zA-Z][a-zA-Z0-9_]*  {return ID;}
[0-9]+ {return NUM;}
"\n" {return NL;}
"\t"|" " {}
. {return yytext[0];}

%%