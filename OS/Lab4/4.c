#include <stdio.h>

int main() {
    int i = 1234;
    float f = 12.345;
    char c = 'A';
    char s[] = "MIT Manipal";
    printf("Integer (%%d): %d\n", i);
    printf("Octal (%%o): %o\n", i);
    printf("Hexadecimal (%%x): %x\n", i);
    printf("Float (%%f): %f\n", f);
    printf("Exponential (%%e): %e\n", f);
    printf("Character (%%c): %c\n", c);
    printf("String (%%s): %s\n", s);
    printf("Pointer (%%p): %p\n", (void*)&i);
    printf("Percentage (%%%%): %%\n");
    return 0;
}
