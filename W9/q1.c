#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[100], input[100];
int top = -1, i = 0;

void push(char c) {
    stack[++top] = c;
}

void pop(int n) {
    top -= n;
}

void printStack() {
    for (int j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

void checkReduce() {

    // F → id
    if (stack[top] == 'i') {
        printf("\nReduce: F → id");
        pop(1);
        push('F');
    }

    // F → (E)
    if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        printf("\nReduce: F → (E)");
        pop(3);
        push('F');
    }

    // T → T * F  (HIGH precedence)
    if (top >= 2 && stack[top] == 'F' && stack[top-1] == '*' && stack[top-2] == 'T') {
        printf("\nReduce: T → T*F");
        pop(3);
        push('T');
    }

    // T → F
    if (stack[top] == 'F') {
        printf("\nReduce: T → F");
        pop(1);
        push('T');
    }

    // ⚠️ FIX: Only reduce E → E+T when safe
    if (top >= 2 && stack[top] == 'T' && stack[top-1] == '+' && stack[top-2] == 'E'
        && (input[i] == '+' || input[i] == '$' || input[i] == ')')) {

        printf("\nReduce: E → E+T");
        pop(3);
        push('E');
    }

    // E → T (also controlled)
    if (stack[top] == 'T' && (input[i] == '+' || input[i] == '$' || input[i] == ')')) {
        printf("\nReduce: E → T");
        pop(1);
        push('E');
    }
}
int main() {
    printf("Enter input string (for id, i): ");
    scanf("%s", input);

    printf("\nStack\tInput\tAction\n");

  while (input[i] != '\0') {

    printf("\n");
    printStack();
    printf("\t%s\t", &input[i]);

    if (input[i] == '$') {
        break;
    }

    printf("Shift %c", input[i]);
    push(input[i]);
    i++;

    int prevTop;
    do {
        prevTop = top;
        checkReduce();
    } while (prevTop != top);
}

    // Final check
    if (top == 0 && stack[top] == 'E') 
    {
        printf("\n\nString Accepted!\n");
    } else 
    {
        printf("\n\nString Rejected!\n");
    }

    return 0;
}
