#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define bufsiz 2024


typedef struct{
	char name[2024];
	int idx;
	unsigned int row, col;
	char type[2024];
	} token;
	
	
char keywords[32][10] = {
    "auto", "break", "case", "char",
    "const", "continue", "default", "do",
    "double", "else", "enum", "extern",
    "float", "for", "goto", "if",
    "int", "long", "register", "return",
    "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

int checkKW(char word[]){
    for(int i=0;i<32;i++){
        if(strcmp(keywords[i], word)==0) return 1;
    }
    return 0;
}
int checkCons(char str[]){
	int f=1;
	for(int i=0;i<strlen(str);i++) if(str[i]>='0' && str[i] <= '9') {} else{f=0; break;}
	return f;

}

void getNextToken(FILE *input){
    int row=1, col=1;
    char c = fgetc(input);
    while(c!=EOF){
    char buf[bufsiz];
    int i=0;
    token s;
    if(isalnum(c) || c == '_' ){
    buf[i++]=c;
    	 c=fgetc(input);
    	 while(isalnum(c) && c!=' '){
    	 buf[i++]=c;
    	 c=fgetc(input);
    	 }
    	 buf[i]='\0';
    	 strcpy(s.name, buf);
    	 s.col=col;
    	 s.row=row;
    	 
    	 if(checkKW(buf)) {
    	 strcpy(s.type, "keyword");
    	 printf("<%s, %d, %d>", s.name,s.row, s.col);}
    	 else if(checkCons(buf)){
    	 strcpy(s.type, "num");
    	  printf("<%s, %d, %d>", s.type,s.row, s.col);
    	  }
    	 else {
    	 strcpy(s.type, "id");
    	 printf("<%s, %d, %d>", s.type,s.row, s.col);}
    	 col+=strlen(buf);
    }
    else if(c == '#'){
        c=fgetc(input);
        while(c!='\n' && c != EOF) c=fgetc(input);
        c=fgetc(input);
        row++;
        col=1;
    }
    else if(c == '"'){
        while((c = fgetc(input)) != '"' && c != EOF) {
                if(c == '\n') row++;
            }
            col++;
    }
    else if(c=='\n'){
    col=1;
    row++;
    printf("\n");
    c=fgetc(input);
    }
    else if(c=='/'){
        c=fgetc(input);
        if(c=='/' ){
            while( c!='\n') c=fgetc(input);
            row++;
            col = 1;
            c=fgetc(input);
        }
        else if(c == '*') {
                char prev = 0;
                while((c = fgetc(input)) != EOF) {
                    if(c == '\n') row++;
                    if(prev == '*' && c == '/') break;
                    prev = c;
                }
                col = 1;
    }
}
    else if(c!=' '){
    
    buf[i++]=c;
    buf[i]='\0';
    strcpy(s.name, buf);
    	 s.col=col;
    	 s.row=row;
    	 
    strcpy(s.type, buf);
    printf("<%s, %d, %d>", s.type,s.row, s.col);
    col+=strlen(buf);
    c=fgetc(input);
    }
    
    else {col++;c=fgetc(input);}

    }
}
	
int main(){
FILE *input;
	char input_file[bufsiz];
    scanf("%s", input_file);
    input = fopen(input_file, "r");
    if(input==NULL){}
    else{
	getNextToken(input);
    
    }
return 0;
}


