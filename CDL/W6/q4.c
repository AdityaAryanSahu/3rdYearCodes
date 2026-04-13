#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int curr=0;
char str[1024];

void L();
void S();
void Lprime();

void invalid()
{
printf("-----------------ERROR!----------------\n");
exit(0);
}
void valid()
{
printf("----------------SUCCESS!---------------\n");
exit(0);
}

void L(){
	S();
	Lprime();
	
}
void Lprime(){
	if(str[curr] == ','){
		curr++;
		S();
		Lprime();
	
	}

}
void S(){
	if(str[curr] == 'a'){
		curr++;
		return;
	}
	else if( str[curr]=='('){
	 curr++;
	 L();
	 	if(str[curr] == ')'){
	 	
	 		curr++;
	 		return;
	 	}
	 	else invalid();
	}
}
int main(){
	printf("enter string\n");
	gets(str);
	S();
	if(str[curr] == '$')
	valid();
	else
	invalid();

}


