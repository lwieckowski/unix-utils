#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            FILE* fp = fopen(argv[i], "rb");
            if (fp == NULL) {
                fprintf(stderr, "wunzip: cannot open file\n");
                exit(1);
            }
            int count;
            char c;
            while (feof(fp) == 0 && ferror(fp) == 0) {
                fread(&count, 4, 1, fp);
                fread(&c, 1, 1, fp);
                while (count-- > 0) {
                    printf("%c", c);
                }
            }
        }
    }
    return 0;
}
