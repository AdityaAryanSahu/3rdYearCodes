#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h> 
#include "la.h"


token tkn;
FILE *ptr;

void error(char*expected){
    printf("error found at row: %d  col: %d \n", tkn.row, tkn.col);
    printf("expected: %s\n", expected);
    printf("found: %s (%s)\n", tkn.lexeme, tkn.type);
    exit(1);
}

void match(char* lexeme){
    if(strcmp(tkn.lexeme, lexeme)==0)
        tkn = getNextToken(ptr);
    else error(lexeme);
}

void matchType(char* type){
    if(strcmp(tkn.type, type)==0)
        tkn = getNextToken(ptr);
    else error(type);
}

void Program();
void declarations();
void identifier_list();
void assign_stat();
void statement();
void statement_list();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void Program(){
    if(strcmp(tkn.lexeme, "main")==0){
        match("main");
        match("(");
        match(")");
        match("{");
        declarations();
        statement_list();
        match("}");

        printf("success\n");
    }
}


void declarations(){
    if (strcmp(tkn.lexeme, "int") == 0 ||
        strcmp(tkn.lexeme, "char") == 0){ 
        if(strcmp(tkn.lexeme, "int")==0) match("int");
    else if(strcmp(tkn.lexeme, "char")==0) match("char");            
        identifier_list();
        match(";");
        declarations();
    }
}

void identifier_list(){
    matchType("IDENTIFIER");
   if(strcmp(tkn.lexeme, "[")==0){
        match("[");
        matchType("NUMBER");
        match("]");
    }
    if (strcmp(tkn.lexeme, ",") == 0) {
        match(",");
        identifier_list();
    }
}

void statement_list(){
     if(strcmp(tkn.type, "IDENTIFIER")==0){
    statement();
    statement_list();
    }
}
void statement(){
    assign_stat();
    match(";");
}

void assign_stat(){
    matchType("IDENTIFIER");
        match("=");
        expn();
}

void expn(){
    simple_exp();
    eprime();
}

void eprime(){
    if (strcmp(tkn.lexeme, "==") == 0 || strcmp(tkn.lexeme, "!=") == 0 ||
        strcmp(tkn.lexeme, "<=") == 0 || strcmp(tkn.lexeme, ">=") == 0 ||
        strcmp(tkn.lexeme, "<") == 0  || strcmp(tkn.lexeme, ">") == 0) {
    relop();
    simple_exp();
        }
}

void simple_exp(){
    term();
    seprime();
}

void seprime(){
     if(strcmp(tkn.lexeme, "+")==0 || strcmp(tkn.lexeme, "-")==0){
    addop();
    term();
    seprime();
    }
}

void term(){
    factor();
    tprime();
}

void tprime(){
    if(strcmp(tkn.lexeme, "*")==0 || strcmp(tkn.lexeme, "/")==0 || strcmp(tkn.lexeme, "%")==0){
    mulop();
    factor();
    tprime();
    }
}

void factor(){
    if(strcmp(tkn.type, "IDENTIFIER")==0) matchType("IDENTIFIER");
    else if(strcmp(tkn.type, "NUMBER")==0) matchType("NUMBER");
    else error("id or num");
}

void relop(){
    if(strcmp(tkn.lexeme, ">")==0) {
        match(">");
    }
    else if(strcmp(tkn.lexeme, "<")==0){
        match("<");
    }
    else  if(strcmp(tkn.lexeme, "==")==0) match("==");
    else  if(strcmp(tkn.lexeme, "<=")==0) match("<=");
    else  if(strcmp(tkn.lexeme, ">=")==0) match(">=");
    else  if(strcmp(tkn.lexeme, "!=")==0) match("!=");
    else error("relop");

    
}
void addop(){
    if(strcmp(tkn.lexeme, "+")==0) match("+");
    else if(strcmp(tkn.lexeme, "-")==0) match("-");
    else error("+ or -");
}

void mulop(){
    if(strcmp(tkn.lexeme, "*")==0) match("*");
    else if(strcmp(tkn.lexeme, "/")==0) match("/");
    else if(strcmp(tkn.lexeme, "%")==0) match("%");
    else error("* / %");
}

int main()
{
    char input[1024];
    printf("enter input file\n");
    gets(input);
    ptr = fopen(input, "r");

    if (ptr == NULL)
    {
        printf("Cannot open file\n");
        return 0;
    }

    tkn = getNextToken(ptr);
    Program();

    fclose(ptr);
    return 0;
}



