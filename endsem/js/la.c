#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char* keywords[] ={
    "let", "if", "else", "while"
};
int row=1, col=1;
typedef struct{
    int row, col;
    char lexeme[100];
    char type[100];
}token;


int check(char*buf){
    for(int i=0;i<4;i++){
        if(strcmp(buf, keywords[i])==0) return 1;
    }
    return 0;
}

void getNextToken(FILE *fp){
    token tkn;
    tkn.lexeme[0]='\0';
    tkn.type[0]='\0';
    char buf[100];
    while(1){
    char c = fgetc(fp);
    if(isspace(c)){
        if(c == '\n'){row++; col=1;}
        else col++;
        continue;
    }
    if(c == '/'){
        c = fgetc(fp);
        if(c == '/'){
            while(c!=EOF && c!='\n'){
                c = fgetc(fp);
            }
            col=1;
            row++;
        }
        else if(c == '*'){
            c = fgetc(fp);
            while(c != EOF){
                if(c == '\n'){ row++; col = 1; }
                if(c == '*'){
                    int d = fgetc(fp);
                    if(d == '/') break;
                    else ungetc(d, fp);
                }
                c = fgetc(fp);
            }
            continue;
        }
        else ungetc(c, fp);
    }

    tkn.col=col;
    tkn.row=row;
    if(c == '"'){
        c=fgetc(fp);
        int i=0;
        while(c!=EOF && c!='"'){
            buf[i++]=c;
            c=fgetc(fp);
        }
        buf[i]='\0';
        c=fgetc(fp);
        col+=strlen(buf)+2;
        strcpy(tkn.lexeme, buf);
        strcpy(tkn.type, "STRING");
        return tkn;
    }

     if(isdigit(c)){
        int i=0;
        while(c!=EOF && isdigit(c)){
            buf[i++]=c;
            c=fgetc(fp);
        }
        buf[i]='\0';
        ungetc(c, fp);
        col+=strlen(buf);
        strcpy(tkn.lexeme, buf);
        strcpy(tkn.type, "NUM");
        return tkn;
    }

    if(isalnum(c) || c == '_'){
        int i=0;
        while(c!=EOF && (isalnum(c) || c == '_')){
            buf[i++]=c;
            c=fgetc(fp);
        }
        buf[i]='\0';
        ungetc(c, fp);
        col+=strlen(buf);
        strcpy(tkn.lexeme, buf);
        if(check(buf))(tkn.type, "KEYWORD");
        else (tkn.type, "ID");
        return tkn;
    }
    if(c == '=' || c == '+' || c == '-' || c == '*' || c == '>' || c=='<'){
        buf[0]=c;
        char d = fgetc(fp);
        if(c == d){
            buf[1] = c;
            col++;
            buf[2]='\0';
        }
        else {ungetc(d, fp); buf[1]='\0';}
        strcpy(tkn.lexeme, buf);
        strcpy(tkn.type, "OP");
    }
    buf[0]=c;
    col++;
    buf[1]='\0';
    strcpy(tkn.lexeme, buf);
    strcpy(tkn.type, "SPECIAL SYMBOL");
    }
   
}