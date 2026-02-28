#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int curr=0;
char str[1024];

void U();
void S();
void W();
void V();

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

void U(){
	if(str[curr] == 'a'){
	curr++;
	 S();
	 if(str[curr] == 'b'){
	 	curr++;
	 	return;
	 }
	 else invalid();
	}
	else if( str[curr] == '('){
	 curr++;
	 S();
	 if( str[curr] == ')'){
	 	curr++;
	 	return;
	 }
	 else invalid();
	
	}
	else if(str[curr] == 'd'){
		curr++;
		return;
	}
	
}
void S(){
	U();
	V();
	W();
	
}
void V(){
	if(str[curr] == 'a'){
			curr++;
			V();
			
	}
}
void W(){
	if(str[curr] == 'c'){
			curr++;
			W();
			
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


