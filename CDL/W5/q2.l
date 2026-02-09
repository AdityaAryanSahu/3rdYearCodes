%{
#include<stdio.h>
int w=1;
int c=0;
int bl=0;
int line=1;
%}

%%
\n {line++;w++;}
" " {bl++;w++;}
\t {bl++;}
. {c++;}
%%

int yywrap() { return 1;}
int main()
{

char stat[20];
printf("Enter your input: ");
//scanf("%s",stat);
yylex();	//reads ther input(no need of scanf)
printf("\nwords= %d characters= %d blanks=%d lines=%d",w,c,bl,line);
}
