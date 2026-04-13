#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "la.h"

token tkn;
FILE* fp;

int error(char* exp){
    printf("error at row: %d col: %d\n", tkn.row, tkn.col);
    printf("expected: %s\n", exp);
    printf("found: %s (%s)\n", tkn.lexeme, tkn.type);
    exit(0);
}


int match(char* lexeme){
    if(strcmp(tkn.lexeme, lexeme)==0)
        tkn = getNextToken(fp);
    else error(lexeme);
}

int matchType(char* type){
    if(strcmp(tkn.type, type)==0)
        tkn = getNextToken(fp);
    else error(type);
}


void Program();
void stmt_list();
void stmt();
void expr();
void exprPrime();
void factor();
void term();
void termPrime();


void Program(){
    stmt_list();
    printf("parsing complete\n");
}

void stmt_list(){
   if(strcmp(tkn.lexeme, "let")==0 || strcmp(tkn.type, "ID")==0){
        stmt();
        stmt_list();
    }
}

void stmt(){
     if(strcmp(tkn.lexeme, "let")==0 || strcmp(tkn.type, "ID")==0){
        if(strcmp(tkn.lexeme, "let")==0) match("let");
        matchType("ID");
        match("=");
        expr();
        match(";");
    }
}

void expr(){
    term();
    exprPrime();
}

void exprPrime(){
    if(strcmp(tkn.lexeme, "+")==0 || strcmp(tkn.lexeme, "-")==0){
        if(strcmp(tkn.lexeme, "+")==0) match("+");
        else match("-");
        term();
        exprPrime();
    }
}

void term(){
    factor();
    termPrime();
}


void termPrime(){
    if(strcmp(tkn.lexeme, "*")==0){
        match("*");
        factor();
        termPrime();
    }
}

void factor(){
    if(strcmp(tkn.type, "ID")==0) matchType("ID");
    else if(strcmp(tkn.type, "NUM")==0) matchType("NUM");
    else if(strcmp(tkn.lexeme, "(")==0){
        match("(");
        expr();
        match(")");
    }
    else error("factor");
}

int main(){
    char filename[1024];
    gets(filename);

    fp = fopen(filename, "r");
    tkn = getNextToken(fp);
    Program();
    return 0;
}