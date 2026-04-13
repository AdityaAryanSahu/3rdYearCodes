#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h> 

typedef struct{
    int row, col;
    char lexeme[1024];
    char type[100];
}token;

int row=1, col=1;

token getNextToken(FILE *ptr){
    token tkn;
    char buf[1024];
    tkn.lexeme[0]='\0';
    tkn.type[0]='\0';
    while(1){
    int c = fgetc(ptr);
    if(isspace(c)){
        if(c == '\n') {col=1; row++;}
        else col++;
        continue;
    }
    if(c == EOF){
        strcpy(tkn.type, "EOF");
        return tkn;
    }

    if(c == '/'){
        c =fgetc(ptr);
        if(c == '/'){
            while(c!=EOF && c !='\n'){
                c = fgetc(ptr);
                col++;
            }
            row++;
            col=1;
            continue; 
        }
        else if(c == '*'){
            c = fgetc(ptr);
            while(c != EOF){
                if(c == '\n'){ row++; col = 1; }
                if(c == '*'){
                    int d = fgetc(ptr);
                    if(d == '/') break;
                    else ungetc(d, ptr);
                }
                c = fgetc(ptr);
                }
                continue;
        }
        else ungetc(c, ptr);
    }

    if(c == '#'){
        while(c!=EOF && c!='\n'){
            col++;
            c=fgetc(ptr);
        }
       // c=fgetc(ptr);
        row++;
        continue; 
    }

    tkn.row=row;
    tkn.col=col;

    if(c == '"'){
        c = fgetc(ptr);
        int i=0;
        while(c != EOF && c != '"'){
            buf[i++]=c;
            c = fgetc(ptr);
        }
        buf[i]='\0';
        col+=strlen(buf)+2;
        strcpy(tkn.lexeme, buf);
        strcpy(tkn.type, "STRING");
        return tkn;
    }

    if(isdigit(c)){
        int i=0;
        buf[i++]=c;
        c=fgetc(ptr);
        while(c!=EOF && isdigit(c)){
            buf[i++]=c;
            c=fgetc(ptr);
        }
        ungetc(c, ptr);
        buf[i]='\0';
        col+=strlen(buf);
        strcpy(tkn.lexeme, buf);
        strcpy(tkn.type, "NUMBER");
        return tkn;
    }

    if(isalnum(c) || c == '_'){
        int i=0;
        buf[i++]=c;
        c=fgetc(ptr);
        while(c!=EOF && (isalnum(c) || c == '_')){
            buf[i++]=c;
            c=fgetc(ptr);
        }
        ungetc(c, ptr);
        buf[i]='\0';
        col+=strlen(buf);
        strcpy(tkn.lexeme, buf);
        strcpy(tkn.type, "IDENTIFIER");
        //else strcpy(tkn.type, "KEYWORD");
        return tkn;
    }
    if(c == '+' || c=='-' || c=='*' || c=='/' || c == '&' || c=='|'|| c=='<' || c=='>' || c=='=' || c =='!'){
        char d = fgetc(ptr);
        if(c == d){
            buf[0]=c;
            buf[1]=c;
            buf[2]='\0';
            col++;
        }
        else if((c == '!' && d=='=') || (c == '<' && d=='=') || (c == '>' && d=='=')){
            buf[0]=c;
            buf[1]=d;
            buf[2]='\0';
            col++;
        }
        else{
            buf[0]=c;
            buf[1]='\0';
            ungetc(d, ptr);
        }
        strcpy(tkn.lexeme, buf);
        strcpy(tkn.type,"OPERATOR");
        return tkn;
    }
    buf[0]=c;
    buf[1]='\0';
    strcpy(tkn.lexeme, buf);
    strcpy(tkn.type,"SPECIAL SYMBOL");
    col++;
    return tkn;
    }

}