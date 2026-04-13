#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "la.h"

token tkn;
FILE* fp;

void error(char*buf){
    printf("error at row: %d col: %d\n", tkn.row, tkn.col);
    printf("expected: %s\n", buf);
    printf("found: %s (%s)\n", tkn.lexeme, tkn.type);
    exit(0);
}

void match(char*buf){
    if(strcmp(buf, tkn.lexeme)==0)
        tkn =getNextToken(fp);
        else error(buf);
}

void matchType(char*buf){
    if(strcmp(buf, tkn.type)==0)
        tkn =getNextToken(fp);
        else error(buf);
}

void Program();
void stmt_list();
void stmt();
void expr();
void exprPrime();
void term();
void factor();
void cond();
void relop();

void Program(){
    stmt_list();
    printf("suceess\n");
}

void stmt_list(){
    if(strcmp(tkn.type, "ID")==0){
        stmt();
        stmt_list();
    }
}

void stmt(){
    if(strcmp(tkn.type, "ID")==0){
        matchType("ID");
        match("=");
        expr();
    }
    else if(strcmp(tkn.lexeme, "if")==0){
        match("if");
        match("(");
        cond();
        match(")");
        stmt();
        match("else");
        stmt();
    }
    else error("stmt error");
}

void expr(){
    term();
    exprPrime();
}
void exprPrime(){
    if(strcmp(tkn.lexeme, "+")==0 || strcmp(tkn.lexeme, "-")==0 ||strcmp(tkn.lexeme, "*")==0){
        if(strcmp(tkn.lexeme, "+")==0) match("+");
        else if(strcmp(tkn.lexeme, "-")==0) match("-");
        else match("*");
        term();
        exprPrime();
    }
}

void term(){
    factor();
}

void factor(){
     if(strcmp(tkn.type, "ID")==0) matchType("ID");
     else  if(strcmp(tkn.type, "NUM")==0) matchType("NUM");
     else error("ID or NUM");
}

void cond(){
    matchType("ID");
    relop();
    matchType("ID");
}

void relop(){
    if(strcmp(tkn.lexeme, ">")==0) match(">");
    else if(strcmp(tkn.lexeme, "<")==0) match(">");
    else if(strcmp(tkn.lexeme, "==")==0) match("==");
    else error("relop");
}

int main(){
    char filename[100];
    gets(filename);
    fp = fopen(filename, "r");

    tkn = getNextToken(fp);
    Program();
    return 0;
}

