#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2 ...]\n", argv[0]);
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            perror("Error opening file");
            continue;
        }
        char line[256];
        int count = 0;
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
            if (++count == 20) {
                printf("--More-- (press any key to continue)\n");
                getchar();
                count = 0;
            }
        }
        fclose(fp);
    }
    return 0;
}
