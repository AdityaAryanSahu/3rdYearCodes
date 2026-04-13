%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUM NL

%%

input : input line
      | 
      ;

line : '\n'
     | exp '\n' { printf("Result = %d\n", $1); }
     ;

exp : NUM                { $$ = $1; }
    | exp exp '+'        { $$ = $1 + $2; }
    | exp exp '-'        { $$ = $1 - $2; }
    | exp exp '*'        { $$ = $1 * $2; }
    | exp exp '/'        { $$ = $1 / $2; }
    | exp exp '^'        { 
                            int res = 1;
                            for(int i=0;i<$2;i++) res *= $1;
                            $$ = res;
                          }
    ;

%%

void yyerror(const char *s)
{
    printf("Invalid Postfix Expression\n");
}

int main()
{
    printf("Enter postfix expressions:\n");
    yyparse();
}
