#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_ENTRIES 100

struct LogEntry {
    int entryNo;
    char sensorNo[10];
    float temperature;
    int humidity;
    int light;
    char time[10];
};

void swapLogEntries(struct LogEntry* entry1, struct LogEntry* entry2) {
    struct LogEntry temp = *entry1;
    *entry1 = *entry2;
    *entry2 = temp;
}

int readLogEntries(const char* filename, struct LogEntry logEntries[], int* numEntries) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    *numEntries = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "EntryNo") != NULL) {
            continue;
        }

        sscanf(line, "%d,%[^,],%f,%d,%d,%[^,]",
               &logEntries[*numEntries].entryNo,
               logEntries[*numEntries].sensorNo,
               &logEntries[*numEntries].temperature,
               &logEntries[*numEntries].humidity,
               &logEntries[*numEntries].light,
               logEntries[*numEntries].time);

        (*numEntries)++;

        if (*numEntries >= MAX_ENTRIES) {
            break;
        }
    }

    fclose(file);

    return 1;
}

void writeLogEntries(const char* filename, const struct LogEntry logEntries[], int numEntries) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    fprintf(file, "EntryNo,sensorNo,Temperature,Humidity,Light,Time\n");

    for (int i = 0; i < numEntries; i++) {
        fprintf(file, "%d,%s,%.2f,%d,%d,%s\n",
                logEntries[i].entryNo,
                logEntries[i].sensorNo,
                logEntries[i].temperature,
                logEntries[i].humidity,
                logEntries[i].light,
                logEntries[i].time);
    }

    fclose(file);
}

void displayLogEntries(const struct LogEntry logEntries[], int numEntries) {
    printf("Log Entries:\n");
    printf("-----------------------\n");
    printf("EntryNo  SensorNo  Temperature  Humidity  Light  Time\n");
    printf("-----------------------\n");

    for (int i = 0; i < numEntries; i++) {
        printf("%-8d %-9s %-12.2f %-9d %-6d %-s\n",
                logEntries[i].entryNo,
                logEntries[i].sensorNo,
                logEntries[i].temperature,
                logEntries[i].humidity,
                logEntries[i].light,
                logEntries[i].time);
    }

    printf("-----------------------\n");
}

int main() {
    struct LogEntry logEntries[MAX_ENTRIES];
    int numEntries = 0;

    const char* filename = "data.csv";

    if (!readLogEntries(filename, logEntries, &numEntries)) {
        return 1;
    }

    for (int i = 0; i < numEntries - 1; i++) {
        for (int j = 0; j < numEntries - i - 1; j++) {
            if (logEntries[j].temperature < logEntries[j + 1].temperature) {
                swapLogEntries(&logEntries[j], &logEntries[j + 1]);
            }
        }
    }

    displayLogEntries(logEntries, numEntries);

    return 0;
}