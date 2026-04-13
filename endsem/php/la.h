#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

typedef struct{
    int row, col;
    char lexeme[100];
    char type[100];
}token;


char* keywords[]={
    "if", "else"
};

int check(char*buf){
    if(strcmp(buf, "if")==0 || strcmp(buf, "else")==0 ) return 1;
    else return 0;
}

int row=1, col=1;

token getNextToken(FILE* fp){
    token tkn;
    char buf[100];
    tkn.lexeme[0]='\0';
    tkn.type[0]='\0';
    while(1){
        char c = fgetc(fp);
        if(isspace(c)){
            if(c == '\n'){row++; col=1;}
            else col++;
            continue;
        }

        if(c == '#'){
            while(c!=EOF && c!='\n'){
                c =fgetc(fp);
            }
            row++;
            col=1;
            c = fgetc(fp);
            continue;
        }

        if(c == '/'){
            c =fgetc(fp);
            if(c == '/'){
                while(c!=EOF && c!='\n'){
                c =fgetc(fp);
            }
            row++;
            col=1;
            c = fgetc(fp);
            continue;
            }
            else if(c == '*'){

            }
            else ungetc(c, fp);    
        
        }
        tkn.col=col;
        tkn.row=row;
        if(c == '"'){
            c = fgetc(fp);
            int i=0;
            while(c!=EOF && c!='"'){
                buf[i++]=c;
                c =fgetc(fp);
            }
            buf[i]='\0';
            c = fgetc(fp);
            col+=strlen(buf)+2;
            strcpy(tkn.lexeme, buf);
            strcpy(tkn.type, "STRING");
            return tkn;

        }
        if(isdigit(c)){
            int i=0;
            while(c!=EOF && isdigit(c)){
                buf[i++]=c;
                c =fgetc(fp);
            }
            buf[i]='\0';
            ungetc(c, fp);
            col+=strlen(buf);
            strcpy(tkn.lexeme, buf);
            strcpy(tkn.type, "NUM");
            return tkn;
        }

        if(isalnum(c) || c == '$'){
            int i=0;
            while(c!=EOF && isalnum(c)){
                buf[i++]=c;
                c =fgetc(fp);
            }
            buf[i]='\0';
            ungetc(c, fp);
            col+=strlen(buf);
            strcpy(tkn.lexeme, buf);
            if(!check(buf)) strcpy(tkn.type, "ID");
            else strcpy(tkn.type, "KEYWORD");
            return tkn;
        }

        if(c == '*' || c=='+' || c=='-' || c == '=' || c=='<' || c=='>'){
            buf[0]=c;
            char d = fgetc(fp);
            if(c==d){
                buf[1]=d;
                col++;
                buf[2]='\0';
            }
            else{
                ungetc(d, fp);
                buf[1]='\0';
            }
            strcpy(tkn.lexeme, buf);
             strcpy(tkn.type, "OP");
             return tkn;
        }
         buf[0]=c;
         buf[1]='\0';
         strcpy(tkn.lexeme, buf);
        strcpy(tkn.type, "SPECIAL SYMBOLS");
        return tkn;
    }
}
