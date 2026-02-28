#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int curr=0;
char str[1024];

void A();
void S();
void B();
void Aprime();
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


void S(){
	if(str[curr] == 'a'){
		curr++;
		A();
		if(str[curr] == 'c'){
		curr++;
		B();
			if(str[curr] == 'e'){
			curr++;
			return;
			}
			else invalid();
		
		}
		else invalid();
	}
	
}
void B(){
	if(str[curr] == 'd'){
			curr++;
			return;
			
	}
	
}
void A(){
	if(str[curr] == 'b'){
			curr++;
			Aprime();
			
	}
	
}
void Aprime(){
	if(str[curr] == 'b'){
			curr++;
			Aprime();
			
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


