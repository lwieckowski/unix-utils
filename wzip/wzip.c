#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    if (argc > 1) {
        char c;
        char c_prev = -1;
        int count = 0;
        for (int i = 1; i < argc; i++) {
            char* filename = argv[i];
            FILE* fp = fopen(filename, "r");
            if (fp == NULL) {
                fprintf(stderr, "wzip: cannot open file\n");
                exit(1);
            }
            while ((c = fgetc(fp)) != EOF) {
                c_prev = c_prev < 0 ? c : c_prev;
                if (c == c_prev) {
                    count++;
                } else {
                    fwrite(&count, 4, 1, stdout);
                    fwrite(&c_prev, 1, 1, stdout);
                    c_prev = c;
                    count = 1;
                }
            }
        }
        fwrite(&count, 4, 1, stdout);
        fwrite(&c_prev, 1, 1, stdout);
    }
    return 0;
}
