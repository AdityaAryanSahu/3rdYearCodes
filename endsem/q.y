%{
#include<stdio.h>
#include<stdlib.h>
int yyerror(const char *s);
int yylex(void);
%}

%token MAIN TYPE ID NUM NL

%%

Program: MAIN '(' ')' '{' declarations assign_stat '}' {printf("parsing success\n");} ;
declarations: data_type identifier_list  ';' declarations 
                |
                ;
data_type: TYPE ;
identifier_list: ID | ID ',' identifier_list ;
assign_stat:  ID '=' ID ';' | ID '=' NUM ';' ;

%%
int yyerror(const char *s){
    printf("Error: %s\n", s);
    return 0;
}

int main(){
    printf("enter input");
    yyparse();
}