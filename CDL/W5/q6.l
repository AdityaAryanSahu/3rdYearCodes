%{
#include<stdio.h>
int s_count=0;
int p_count=0;
%}

%%
[a-z]  {printf("%c",yytext[0]-32); }
[A-Z] {printf("%c",yytext[0]+32); }
 /* "//"[a-z]* {
   char c;
   while ((c = input()) != '\n' && c != 1); 
    printf("%s",yytext);
	}*/
"//" {
    printf("%s", yytext); 
    char c;
    while ((c = input()) != '\n' && c != 0) {
        putchar(c);     
    }
    if (c == '\n') putchar('\n');
}
.        { printf("%s", yytext); }
\n       { printf("%s", yytext); }
%%

int yywrap() { return 1; }

int main()
{
    
  FILE *fp;
  printf("Enter file name: ");
  char str[100];
  scanf("%s",str);
    fp = fopen(str, "r");
    if(fp==NULL)
    {
    	printf("Error haha");
    	return 1;
    }
	yyin=fp;
    yylex();

    //printf("Number of scanf: %d\n", s_count);
   // printf("Number of printf: %d\n", p_count);
    
    return 0;
}
