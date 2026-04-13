#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h> 

char stack[100];
 char input[1024];
int top=-1, i;

void push(char c){
    stack[++top]=c;
}

void pop(int n){
    top-=n;
}

void reduce(){
    
    if(stack[top] == 'i'){
        pop(1);
        push('F');
    }

    if(top>=2 && stack[top]==')' && stack[top-1]=='E' && stack[top-2]=='('){
        pop(3);
        push('F');
    }

    if(top>=2 && stack[top]=='F' && stack[top-1]=='*' && stack[top-2]=='T'){
        pop(3);
        push('T');
    }


    if(stack[top]=='F'){
        pop(1);
        push('T');
    }

     if (top >= 2 && stack[top] == 'T' && stack[top-1] == '+' && stack[top-2] == 'E'
        && (input[i] == '+' || input[i] == '$' || input[i] == ')')) {
        pop(3);
        push('E');
    }


    if (stack[top] == 'T' && (input[i] == '+' || input[i] == '$' || input[i] == ')')) {
        pop(1);
        push('E');
    }

   
}

int main(){
   
    gets(input);
    int i=0;
    while(input[i]!='\0'){
        if(input[i]=='$') break;

        push(input[i]);
        i++;
        
        int prev;
        do{
            prev=top;
            reduce();
        } while(prev!=top);
    }

    if(top==0 && stack[top]=='E'){
        printf("success\n");
    }
    else printf("failure\n");
}