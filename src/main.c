#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(FILE *arch, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Could not open %s\n", filename);
        return;
    }

    unsigned char name_len = (unsigned char)strlen(filename);
    fwrite(&name_len, 1, 1, arch);
    fwrite(filename, 1, name_len, arch);

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    fwrite(&size, sizeof(long), 1, arch);

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), f)) > 0) {
        fwrite(buffer, 1, bytes, arch);
    }

    fclose(f);
    printf("Added: %s (%ld bytes)\n", filename, size);
}

void printhelp() {
    printf("Options:\n\t-h: Help\n\t-c: Create and Compress an archive\n\t-a: Add a file to an archive\n\t-d: Decompress and extract an archive");
}

int main(int argc, char *argv[]) {
    if ((argc - 1) < 2) {
        perror("Usage:\n\trzip <options> <arguments>");
        return 1;
    }
    
    char option = argv[1][1];
    switch(option) {
        case 'h':
            printhelp();
            return 0;
        case 'c':
            FILE *arch = fopen(argv[2], "wb");
            if (!arch) {
                perror("Failed to create archive");
                return 1;
            }
        case 'a':
            FILE *arch = fopen("");
            add(archive, argv[3]);
        default:
            printf("Unknown Option \"-%c\"", option);
    }
}