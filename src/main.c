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

void extract(FILE *arch) {
    printf("Not implemented yet...");
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
            fclose(arch);
            break;
        case 'a':
            FILE *archive = fopen(argv[2], "wb");
            if (!archive) {
                perror("Failed to open archive");
                return 1;
            }
            add(archive, argv[3]);
            fclose(archive);
            break;
        case 'd':
            FILE *to_decompress = fopen(argv[2], "rb");
            if (!to_decompress) {
                perror("Failed to open archive");
                return 1;
            }
            extract(to_decompress);
            fclose(to_decompress);
            break;
        default:
            printf("Unknown Option \"-%c\"", option);
            return 1;
    }

    return 0;
}