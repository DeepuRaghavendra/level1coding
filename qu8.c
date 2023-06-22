#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void convertToUpperCase(FILE *sourceFile, FILE *targetFile) {
    int ch;
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(toupper(ch), targetFile);
    }
}

void convertToLowerCase(FILE *sourceFile, FILE *targetFile) {
    int ch;
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(tolower(ch), targetFile);
    }
}

void convertToSentenceCase(FILE *sourceFile, FILE *targetFile) {
    int ch;
    int isFirstCharacter = 1;
    while ((ch = fgetc(sourceFile)) != EOF) {
        if (isFirstCharacter) {
            fputc(toupper(ch), targetFile);
            isFirstCharacter = 0;
        } else {
            fputc(tolower(ch), targetFile);
        }
        if (ch == '.' || ch == '!' || ch == '?') {
            isFirstCharacter = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Insufficient arguments.\n");
        printf("Usage: ./cp <option> <source_file> <target_file>\n");
        return 1;
    }

    char *option = argv[1];
    char *sourceFileName = argv[2];
    char *targetFileName = argv[3];

    FILE *sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        printf("Failed to open the source file.\n");
        return 1;
    }

    FILE *targetFile = fopen(targetFileName, "w");
    if (targetFile == NULL) {
        printf("Failed to create the target file.\n");
        fclose(sourceFile);
        return 1;
    }

    if (strcmp(option, "-u") == 0) {
        convertToUpperCase(sourceFile, targetFile);
    } else if (strcmp(option, "-l") == 0) {
        convertToLowerCase(sourceFile, targetFile);
    } else if (strcmp(option, "-s") == 0) {
        convertToSentenceCase(sourceFile, targetFile);
    } else {
        int ch;
        while ((ch = fgetc(sourceFile)) != EOF) {
            fputc(ch, targetFile);
        }
    }

    printf("File copied successfully.\n");

    fclose(sourceFile);
    fclose(targetFile);

    return 0;
}