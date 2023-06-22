#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deleteLogEntry(const char* filename, int entryNo) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Failed to create temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentEntryNo = atoi(strtok(line, ","));
        if (currentEntryNo != entryNo) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.csv", filename);

    printf("Entry with EntryNo %d deleted successfully.\n", entryNo);
}

int main() {
    int entryNo;
    printf("Enter the EntryNo to delete: ");
    scanf("%d", &entryNo);

    deleteLogEntry("data.csv", entryNo);

    return 0;
}