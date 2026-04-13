#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        exit(1);
    }
    FILE *fp = fopen(argv[2], "r");
    if (!fp) {
        perror("File open error");
        exit(1);
    }
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[1]))
            printf("%s", line);
    }
    fclose(fp);
    return 0;
}
