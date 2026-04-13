%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex(void);
%}

%token TYPE ID NL

%%

stmt : TYPE ID ';' NL   { printf("Valid Declaration\n"); exit(0); }
     ;

%%

void yyerror(const char *s)
{
    printf("Invalid Declaration\n");
    exit(0);
}

int main()
{
    printf("Enter declaration:\n");
    yyparse();
}
