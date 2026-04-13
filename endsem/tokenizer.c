#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h> 



char *keywords[] = 
{"int", "float", "char", "if", "else", "while", "return", 
    "for", "do", "switch", "case", "break", "continue", 
    "void", "struct", "double", "long", "short", "sizeof", "typedef", "const", "exit", NULL};

typedef struct{
    int row, col;
    char lexeme[1024];
    char type[100];
}token;
int row = 1, col = 1;


int isKey(char* word){
    for(int i=0;i<23;i++){
        if(strcmp(keywords[i], word)==0) return 1;
    }
    return 0;
}

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
        c = fgetc(ptr);
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
    if(c == '+' || c=='-' || c=='*' || c=='/' || c == '&' || c=='|'|| c=='<' || c=='>' || c=='='){
        char d = fgetc(ptr);
        if(c == d){
            buf[0]=c;
            buf[1]=c;
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

int main(){
    char filename[1024];
    gets(filename);
    FILE *ptr = fopen(filename, "r");
    if(ptr == NULL){
    printf("File not found\n");
    return 1;
}
    token t; 
    while(1){
        t = getNextToken(ptr);
        if(strcmp(t.type, "EOF")==0) break;
        printf("< %s , %s , %d , %d >\n", t.lexeme,t.type,t.row,t.col);
    }
}