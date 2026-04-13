#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define bufsiz 2024

char keywords[32][10] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};

int checkKW(char word[]){
    for(int i=0;i<32;i++){
        if(strcmp(keywords[i], word)==0) return 1;
    }
    return 0;
}


int isArth(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/') return 1;
    return 0;
}


int isSpecial(char c){
    if(c==';'||c==','||c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']')
        return 1;
    return 0;
}


int isRel(FILE **ip, char c){
    char buf[bufsiz];
    int i=0;

    if(c=='='){
        buf[i++]=c;
        char next=fgetc(*ip);
        if(next=='='){
            buf[i++]=next;
            buf[i]='\0';
            printf("%s is relational op\n", buf);
            return 1;
        }
        else{
            buf[i]='\0';
            printf("%s is assignment op\n", buf);
            ungetc(next,*ip);
            return 1;
        }
    }
    else if(c=='>' || c=='<' || c=='!'){
        buf[i++]=c;
        char next=fgetc(*ip);
        if(next=='='){
            buf[i++]=next;
            buf[i]='\0';
            printf("%s is relational op\n", buf);
            return 1;
        }
        else{
            buf[i]='\0';
            printf("%s is relational op\n", buf);
            ungetc(next,*ip);
            return 1;
        }
    }
    return 0;
}


int isLog(FILE **ip, char c){
    char buf[bufsiz];
    int i=0;

    if(c=='&'){
        buf[i++]=c;
        char next=fgetc(*ip);
        if(next=='&'){
            buf[i++]=next;
            buf[i]='\0';
            printf("%s is logical op\n", buf);
            return 1;
        }
        else ungetc(next,*ip);
    }
    else if(c=='|'){
        buf[i++]=c;
        char next=fgetc(*ip);
        if(next=='|'){
            buf[i++]=next;
            buf[i]='\0';
            printf("%s is logical op\n", buf);
            return 1;
        }
        else ungetc(next,*ip);
    }
    return 0;
}


int checkCons(char str[]){
    int f=1;
    for(int i=0;i<strlen(str);i++)
        if(str[i]>='0' && str[i]<='9'){}
        else{ f=0; break; }
    return f;
}


void checkStr(FILE **ip, char c){
    char buf[bufsiz];
    int i=0;

    buf[i++]=c;
    c=fgetc(*ip);

   
    while(isalnum(c) || c=='_'){
        buf[i++]=c;
        c=fgetc(*ip);
    }
    buf[i]='\0';

    if(checkKW(buf)) printf("%s is keyword\n", buf);
    else if(checkCons(buf)) printf("%s is constant\n", buf);
    else printf("%s is identifier\n", buf);

    ungetc(c,*ip);
}


void StringLit(FILE **ip , char c){
    char buf[bufsiz];
    int i=0;
    c=fgetc(*ip);
    while(c!='"' && c!=EOF){
        buf[i++]=c;
        c=fgetc(*ip);
    }
    buf[i]='\0';
    printf("%s is string literal\n", buf);
}


int main(){
    FILE *input;
    char input_file[bufsiz];
    scanf("%s", input_file);
    input = fopen(input_file, "r");

    if(input==NULL) return 0;

    char c = fgetc(input);

    while(c!=EOF){

        if(isArth(c)){
            printf("%c is arithmetic op\n", c);
            c=fgetc(input);
        }

        else if(isRel(&input,c)){
            c=fgetc(input);
        }

        else if(isLog(&input,c)){
            c=fgetc(input);
        }

       
        else if(isSpecial(c)){
            printf("%c is special symbol\n",c);
            c=fgetc(input);
        }

        else if(c=='"'){
            StringLit(&input,c);
            c=fgetc(input);
        }

        else if(isalnum(c) || c=='_'){
            checkStr(&input,c);
            c=fgetc(input);
        }

        else c=fgetc(input);
    }
}
