%{
#include "js.tab.h"
%}

%%

"let" {return LET;}
[+-] {return ADOP;}
"*" {return MULOP;}
[a-zA-Z][a-zA-Z0-9_]* {return ID;}
[0-9]+ {return NUM;}
[\t ] {}
. {return yytext[0];}

%%