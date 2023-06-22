// 1. File Copy: Write a C program to copy a file using file operations

#include <stdio.h>

int main() {
    FILE *sourceFile, *targetFile;
    char sourceFileName[100], targetFileName[100];
    char ch;

    printf("Enter the source file name: ");
    scanf("%s", sourceFileName);

    sourceFile = fopen(sourceFileName, "r");

    if (sourceFile == NULL) {
        printf("Failed to open the source file.\n");
        return 1;
    }

    printf("Enter the target file name: ");
    scanf("%s", targetFileName);

    targetFile = fopen(targetFileName, "w");

    if (targetFile == NULL) {
        printf("Failed to create the target file.\n");
        fclose(sourceFile);
        return 1;
    }

    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, targetFile);
    }

    printf("File copied successfully.\n");

    fclose(sourceFile);
    fclose(targetFile);

    return 0;
}