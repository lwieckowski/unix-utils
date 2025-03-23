#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 1024

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            char* filename = argv[i];
            FILE* fp = fopen(filename, "r");
            if (fp == NULL) {
                printf("wcat: cannot open file %s\n", filename);
                exit(1);
            }
            fseek(fp, 0, SEEK_END);
            int n_bytes = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            if (errno) {
                printf("wcat: error reading from file %s\n", filename);
                exit(1);
            }
            int offset = 0;
            int buffer_size = (n_bytes < BUFSIZE) ? n_bytes : BUFSIZE;
            while (offset < n_bytes) {
                char* buffer = (char*)malloc(sizeof(char) * buffer_size);
                if (buffer == NULL) {
                    printf("wcat: could not allocate memory\n");
                    exit(1);
                }
                fread(buffer, sizeof(char), buffer_size, fp);
                if (ferror(fp)) {
                    printf("wcat: error reading from file %s\n", filename);
                    exit(1);
                }
                printf("%s", buffer);
                offset += BUFSIZE;
            }
            fclose(fp);
        }
    }
    return 0;
}
