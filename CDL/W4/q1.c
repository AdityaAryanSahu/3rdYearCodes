#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define bufsiz 2024
#define TableLength 100


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


enum tokenType { EOFILE=-1, LESS_THAN,
LESS_THAN_OR_EQUAL,GREATER_THAN,GREATER_THAN_OR_EQUAL,
EQUAL,NOT_EQUAL};

struct ListElement{
	token tok;
	struct ListElement *next;
};

int HASH(char *str){
int sum=0;
for(int i=0;i<strlen(str);i++) sum+=str[i];
return sum % 100;

}
struct ListElement *TABLE[TableLength];

void Initialize(){
	for(int i=0;i<TableLength;i++){
	TABLE[i] = NULL;
}
}

int SEARCH(char *str){
	int val = HASH(str);
	for(struct ListElement *temp = TABLE[val]; temp!=NULL; temp=temp->next){
 		token s= temp->tok;
 		if(strcmp(s.name, str) == 0) return 1;
 	}
 	return 0;
	
}
void display(){

 for(int i=0;i<TableLength;i++){
 	if(!TABLE[i]){
 	for(struct ListElement *temp = TABLE[i]; temp!=NULL; temp=temp->next){
 		token s= temp->tok;
 		printf("%s\t%s\n",  s.name,  s.type);
 	}
 	
 	}
 
 }

}

void INSERT(token tk){
if(SEARCH(tk.name)==1){
return;
}

struct ListElement* cur = (struct ListElement*)malloc(sizeof(struct ListElement));
cur->tok = tk;
cur->next = NULL;
int val = HASH(tk.name);
if(TABLE[val]==NULL){
TABLE[val] = cur; // No collosion.
}
else{
struct ListElement * ele= TABLE[val];
while(ele->next!=NULL){
ele = ele->next; // Add the element at the End in the case of a //collision.
}
ele->next = cur;
}}

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
    	 }
    	 else if(checkCons(buf)){
    	 strcpy(s.type, "num");
    	  }
    	 else {
    	 strcpy(s.type, "id");
    	
    	 if(c=='('){
    	 printf("%s\n", s.name);
    	 INSERT(s);
    	 } else c =ungetc(c, input);}
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
	display();
    
    }
return 0;
}
