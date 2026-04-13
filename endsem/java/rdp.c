#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include "la.h"
token tkn;
FILE* fp;

void error(char*exp){
    printf("error at row:%d col:%d\n", tkn.row, tkn.col);
    printf("expected: %s\n", exp);
    printf("found: %s\n", tkn.lexeme);
    exit(0);
}

void match(char* buf){
    if(strcmp(tkn.lexeme, buf)==0)
        tkn = getNextToken(fp);
    else error(buf);
}

void matchType(char* buf){
    if(strcmp(tkn.type, buf)==0)
        tkn = getNextToken(fp);
    else error(buf);
}

void Program();
void decls();
void decl();
void type();
void id_list();
void id_tail();
void stmts();
void stmt();
void expr();
void exprPrime();
void term();

void Program(){
    if(strcmp(tkn.lexeme, "main")==0){
        match("main");
        match("(");
        match(")");
        match("{");
        decls();
        stmts();
        printf("parsing complete\n");
    }
}

void decls(){
    if(strcmp(tkn.lexeme, "int")==0 || strcmp(tkn.lexeme, "float")==0 || strcmp(tkn.lexeme, "char")==0){
        decl();
        decls();
    }
}

void decl(){
    type();
    id_list();
    match(";");
}

void type(){
    if(strcmp(tkn.lexeme, "int")==0) match("int");
    else if(strcmp(tkn.lexeme, "float")==0) match("float");
    else if(strcmp(tkn.lexeme, "char")==0) match("char");
    else error("type error");
}

void id_list(){
    matchType("ID");
    id_tail();
}

void id_tail(){
    if(strcmp(tkn.lexeme, ",")==0){
        match(",");
        matchType("ID");
        id_tail();
    }
}

void stmts(){
    if(strcmp(tkn.type, "ID")==0){
        stmt();
        stmts();
    }
}

void stmt(){
        matchType("ID");
        match("=");
        expr();
        match(";");
}

void expr(){
    term();
    exprPrime();
}

void exprPrime(){
    if(strcmp(tkn.lexeme, "+")==0 || strcmp(tkn.lexeme, "-")==0 || strcmp(tkn.lexeme, "*")==0 ){
        if(strcmp(tkn.lexeme, "+")==0) match("+");
        else if(strcmp(tkn.lexeme, "-")==0) match("-");
        else match("*");
        term();
        exprPrime();
    }
}

void term(){
    if(strcmp(tkn.type, "ID")==0) matchType("ID");
    else if(strcmp(tkn.type, "NUM")==0) matchType("NUM");
    else error("ID OR NUM");
}

int main(){
    char filename[100];
    gets(filename);
    fp = fopen(filename, "r");
    tkn = getNextToken(fp);
    Program();
    return 0;
}




