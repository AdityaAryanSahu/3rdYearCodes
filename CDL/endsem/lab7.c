#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h> 
#include "la.h"


token tkn;
FILE *ptr;

void error(char*buf){
    printf("\nERROR at row %d col %d\n", tkn.row, tkn.col);
    printf("Expected: %s\n", buf);
    printf("Found : %s (%s)\n", tkn.lexeme, tkn.type);
    exit(0);
}

int match(char buf[]){
    if(strcmp(tkn.lexeme, buf)==0){
        tkn = getNextToken(ptr);
    }
    else error(buf);
}

int matchType(char buf[]){
    if(strcmp(tkn.type, buf)==0){
        tkn = getNextToken(ptr);
    }
    else error(buf);
}


void Program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();


void Program(){
    if(strcmp(tkn.lexeme, "main")==0){
    match("main");
    match("(");
    match(")");
    match("{");
    declarations();
    assign_stat();
    match("}");
    printf("\nSUCCESS: Valid Program\n");
    }
}

void declarations(){
    if (strcmp(tkn.lexeme, "int") == 0 ||
        strcmp(tkn.lexeme, "char") == 0){
    data_type();
    identifier_list();
    match(";");
    declarations();
        }
}

void data_type(){
    if(strcmp(tkn.lexeme, "int")==0) match("int");
    else if(strcmp(tkn.lexeme, "char")==0) match("char");
    else
        error("int or char");
}

void identifier_list(){
    matchType("IDENTIFIER");
    if (strcmp(tkn.lexeme, ",") == 0)
    {
        match(",");
        identifier_list();
    }
}

void assign_stat(){
    matchType("IDENTIFIER");
    match("=");
    if(strcmp(tkn.type, "IDENTIFIER")==0) matchType("IDENTIFIER");
    else if(strcmp(tkn.type, "NUMBER")==0) matchType("NUMBER");
    else
        error("id or num");
    match(";");

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