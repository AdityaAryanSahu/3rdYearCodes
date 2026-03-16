#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

struct token lookahead;
FILE *fp;

void error(char *expected)
{
    printf("\nERROR at row %d col %d\n", lookahead.row, lookahead.col);
    printf("Expected: %s\n", expected);
    printf("Found   : %s (%s)\n", lookahead.lexeme, lookahead.type);
    exit(0);
}

void match(char *lex)
{
    if (strcmp(lookahead.lexeme, lex) == 0)
        lookahead = getNextToken(fp);
    else
        error(lex);
}

void matchType(char *type)
{
    if (strcmp(lookahead.type, type) == 0)
        lookahead = getNextToken(fp);
    else
        error(type);
}


void Program();
void declarations();
void datatype();
void identifier_list();
void assign_stat();

void Program()
{
    if (strcmp(lookahead.lexeme, "main") == 0)
    {
        match("main");
        match("(");
        match(")");
        match("{");
        declarations();
        assign_stat();
        match("}");
        printf("\nSUCCESS: Valid Program\n");
    }
    else
        error("main");
}

void declarations()
{
    if (strcmp(lookahead.lexeme, "int") == 0 ||
        strcmp(lookahead.lexeme, "char") == 0)
    {
        datatype();
        identifier_list();
        match(";");
        declarations();   // recursion
    }
    // else epsilon
}

void datatype()
{
    if (strcmp(lookahead.lexeme, "int") == 0)
        match("int");
    else if (strcmp(lookahead.lexeme, "char") == 0)
        match("char");
    else
        error("int or char");
}

void identifier_list()
{
    matchType("Identifier");

    if (strcmp(lookahead.lexeme, ",") == 0)
    {
        match(",");
        identifier_list();
    }
}

void assign_stat()
{
    matchType("Identifier");
    match("=");
    
    if (strcmp(lookahead.type, "Identifier") == 0)
        matchType("Identifier");
    else if (strcmp(lookahead.type, "Number") == 0)
        matchType("Number");
    else
        error("Identifier or Number");

    match(";");
}

/* ---------- Main ---------- */

int main()
{
    char input[1024];
    printf("enter input file\n");
    gets(input);
    fp = fopen(input, "r");

    if (fp == NULL)
    {
        printf("Cannot open file\n");
        return 0;
    }

    lookahead = getNextToken(fp);
    Program();

    fclose(fp);
    return 0;
}
