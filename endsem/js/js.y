%{
#include<stdio.h>
#include<stdlib.h>
int yyerror(const char*s);
int yylex(void);
%}

%token LET ID MULOP ADOP NUM

%%
Program: stmt_list {printf("success\n");}
        ;

stmt_list: stmt stmt_list
        |
        ;

stmt: LET ID '=' expr ';'
    | ID '=' expr ';'
    ;

expr: term exprPrime
    ;

exprPrime: ADOP term exprPrime
        | 
        ;

term: factor termPrime
    ;

termPrime: MULOP factor termPrime
        |
        ;

factor: ID
        | NUM
        | '(' expr ')'
        ;
%%

int yyerror(const char*s){
    printf("error");
    return 1;
}

int main(){
    printf("enter input");
    yyparse();
}
