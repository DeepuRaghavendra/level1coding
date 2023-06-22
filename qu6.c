#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LogEntry {
    int entryNo;
    char sensorNo[3];
    float temperature;
    int humidity;
    int light;
    char time[9];
};

void deleteLogEntry(struct LogEntry logEntries[], int numEntries, int entryNo) {
    FILE* file = fopen("data.csv", "r");
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

    remove("data.csv");
    rename("temp.csv", "data.csv");

    printf("Entry with EntryNo %d deleted successfully.\n", entryNo);
}

int main() {
    int entryNo;
    printf("Enter the EntryNo to delete: ");
    scanf("%d", &entryNo);

    struct LogEntry logEntries[100];  // Assuming a maximum of 100 entries
    int numEntries = 0;

    FILE* file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        struct LogEntry newEntry;
        sscanf(line, "%d,%[^,],%f,%d,%d,%[^,]", &newEntry.entryNo, newEntry.sensorNo, &newEntry.temperature,
               &newEntry.humidity, &newEntry.light, newEntry.time);

        logEntries[numEntries] = newEntry;
        numEntries++;
    }

    fclose(file);

    deleteLogEntry(logEntries, numEntries, entryNo);

    return 0;
}