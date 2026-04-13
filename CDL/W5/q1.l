%{
#include<stdio.h>
int vow=0;
int cons=0;
%}

%%
[aeiouAEIOU] {vow++;}
[a-zA-Z] {cons++;}
\n {return 0;}
. {;}
%%

int yywrap() { return 1;}
int main()
{

char stat[20];
printf("Enter your input: ");
//scanf("%s",stat);
yylex();	//reads ther input(no need of scanf)
printf("vpw= %d copns= %d",vow,cons);
}
