%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+  { 
            
            int decimal = atoi(yytext); //str to int conv
           
            printf("%X", decimal); 
        }

.       { printf("%s", yytext); } /* Pass through all other characters */
\n      { printf("%s", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter decimal numbers:\n");
    yylex();
    return 0;
}
