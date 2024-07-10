// a. Emulate mv Command:

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (rename(argv[1], argv[2]) == -1) {
        perror("mv");
        exit(EXIT_FAILURE);
    }
    printf("Moved '%s' to '%s'\n", argv[1], argv[2]);
    return 0;
}

// b. Emulate grep Command:

#include <stdio.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pattern>\n", argv[0]);
        return 1;
    }
    char pattern[MAX_LINE_LENGTH];
    strcpy(pattern, argv[1]);
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (strstr(line, pattern) != NULL)
        {
            printf("%s", line);
        }
    }
    return 0;
}