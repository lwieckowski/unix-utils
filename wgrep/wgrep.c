#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    if (argc >= 2) {
        char* term = argv[1];
        FILE* fp;
        size_t bufsize = BUFSIZE;
        char* line = (char*)malloc(BUFSIZE);
        for (int i = 1; i < argc; i++) {
            if (argc == 2) {
                fp = stdin;
            } else if (i == 1) {
                continue;
            } else {
                char* filename = argv[i];
                fp = fopen(filename, "r");
            }
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            while (getline(&line, &bufsize, fp) > 0) {
                if (strstr(line, term) != NULL) {
                    printf("%s", line);
                }
            }
        }
    }
    return 0;
}