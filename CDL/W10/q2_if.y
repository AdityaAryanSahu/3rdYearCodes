%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex(void);
%}

%token IF ELSE ID NUM NL

%%

stmt : IF '(' cond ')' '{' stmt '}' ELSE '{' stmt '}' NL
        { printf("Valid If-Else Statement\n"); exit(0); }
     | ID ';'
     ;

cond : ID
     | NUM
     ;

%%

void yyerror(const char *s)
{
    printf("Invalid If-Else Statement\n");
    exit(0);
}

int main()
{
    printf("Enter if-else:\n");
    yyparse();
}
