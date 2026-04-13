#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "la.h"

token tkn;
FILE* fp;

void error(char* exp){
    printf("error at row:%d col:%d\n", tkn.row, tkn.col);
    printf("expected: %s\n", exp);
    printf("found: %s\n", tkn.lexeme);
    exit(0);
}

void match(char* lex){
    if(strcmp(tkn.lexeme, lex) == 0)
        tkn = getNextToken(fp);
    else error(lex);
}

void matchType(char* type){
    if(strcmp(tkn.type, type) == 0)
        tkn = getNextToken(fp);
    else error(type);
}

// grammar functions
void Document();
void element();
void content();
void tag();
void text();

void Document(){
    element();
    if(strcmp(tkn.type, "EOF") != 0)
        error("EOF");
    printf("Parsing successful\n");
}

void element(){
    match("<");
    tag();
    match(">");
    content();
    match("<");
    match("/");
    tag();
    match(">");
}

void content(){
    if(strcmp(tkn.lexeme, "<") == 0){
        element();
        content();
    }
    else if(strcmp(tkn.type, "STRING") == 0){
        text();
        content();
    }
    // ε
}

void tag(){
    matchType("ID");
}

void text(){
    matchType("STRING");
}

int main(){
    char fname[100];
    gets(fname);
    fp = fopen(fname, "r");
    tkn = getNextToken(fp);
    Document();
    return 0;
}