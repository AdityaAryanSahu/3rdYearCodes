#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX 100

typedef struct{
    char lexeme[100];
    char type[50];
    int row, col;
} token;

char keywords[32][10] = {
 "auto","break","case","char","const","continue","default","do",
 "double","else","enum","extern","float","for","goto","if",
 "int","long","register","return","short","signed","sizeof","static",
 "struct","switch","typedef","union","unsigned","void","volatile","while"
};

int row=1, col=0;



int isKeyword(char *word){
    for(int i=0;i<32;i++)
        if(strcmp(word,keywords[i])==0)
            return 1;
    return 0;
}

int isNumber(char *str){
    for(int i=0;i<strlen(str);i++)
        if(!isdigit(str[i]))
            return 0;
    return 1;
}



void skipPreprocessor(FILE *fp){
    char c;
    while((c=fgetc(fp))!='\n' && c!=EOF);
    row++; col=0;
}

void skipSingleComment(FILE *fp){
    char c;
    while((c=fgetc(fp))!='\n' && c!=EOF);
    row++; col=0;
}

void skipMultiComment(FILE *fp){
    char c, prev=0;
    while((c=fgetc(fp))!=EOF){
        if(c=='\n'){ row++; col=0; }
        if(prev=='*' && c=='/') break;
        prev=c;
    }
}

void skipString(FILE *fp){
    char c;
    while((c=fgetc(fp))!=EOF){
        if(c=='\\') fgetc(fp);   
        else if(c=='"') break;
        else if(c=='\n'){ row++; col=0; }
    }
}



token getNextToken(FILE *fp){
    token t;
    char c, buf[100];
    int i=0;

    while((c=fgetc(fp))!=EOF){
        col++;

       
        if(isspace(c)){
            if(c=='\n'){ row++; col=0; }
            continue;
        }

       
        if(c=='#'){ skipPreprocessor(fp); continue; }

       
        if(c=='/'){
            char next=fgetc(fp);
            if(next=='/') { skipSingleComment(fp); continue; }
            else if(next=='*'){ skipMultiComment(fp); continue; }
            else ungetc(next,fp);
        }

        
        if(c=='"'){ skipString(fp); continue; }

        t.row=row;
        t.col=col;

        
        if(isalpha(c) || c=='_'){
            buf[i++]=c;
            while(isalnum(c=fgetc(fp)) || c=='_'){
                buf[i++]=c; col++;
            }
            buf[i]='\0';
            ungetc(c,fp);

            strcpy(t.lexeme,buf);
            if(isKeyword(buf)) strcpy(t.type,"KEYWORD");
            else strcpy(t.type,"IDENTIFIER");

            return t;
        }

        
        if(isdigit(c)){
            buf[i++]=c;
            while(isdigit(c=fgetc(fp))){
                buf[i++]=c; col++;
            }
            buf[i]='\0';
            ungetc(c,fp);

            strcpy(t.lexeme,buf);
            strcpy(t.type,"NUMBER");
            return t;
        }

       
        t.lexeme[0]=c;
        t.lexeme[1]='\0';
        strcpy(t.type,"SYMBOL");
        return t;
    }

    strcpy(t.type,"EOF");
    return t;
}



int main(){
    FILE *fp;
    char filename[100];
    scanf("%s",filename);

    fp=fopen(filename,"r");
    if(!fp){ printf("File not found"); return 0; }

    token t;
    while(1){
        t=getNextToken(fp);
        if(strcmp(t.type,"EOF")==0) break;
        printf("< %s , %s , %d , %d >\n", t.lexeme,t.type,t.row,t.col);
    }
}
