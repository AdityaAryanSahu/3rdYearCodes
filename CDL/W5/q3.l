%{
#include<stdio.h>
int p=0,n=0,pf=0,nf=0;
%}

%%
[-][0-9]+ {n++;}
[0-9]+ {p++;}
"-"[0-9]+\.[0-9]+ {nf++;}
[0-9]+\.[0-9]+ {pf++;}
%%

int yywrap() { return 1;}
int main()
{

char stat[20];
printf("Enter your input: ");
//scanf("%s",stat);
yylex();	//reads ther input(no need of scanf)
	printf("\npositive= %d negative= %d pos_float=%d  neg_float=%d",p,n,pf,nf);
}
