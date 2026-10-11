#include "File.h"

#include <stdio.h>
#include <string.h>

static size_t GetLineCount(FILE* fptr);
static bool ReadLine(char* buff, int length, FILE* fptr);

bool InitFile(WrFile* file, const char* path) {
    FILE* fptr = fopen(path, "r");
    if (!fptr) return false;

    size_t count = GetLineCount(fptr);
    if (count == 0) {
        fclose(fptr);

        return false;
    }

    file->data = calloc(count, sizeof *file->data);
    if (!file->data) {
        fclose(fptr);

        return false;
    }

    file->lineCount = count;

    for (size_t i = 0; i < file->lineCount; i++) {
        file->data[i] = calloc(WR_FILE_LINE_MAX_LENGTH, sizeof *file->data[i]);
        if (!file->data[i] || !ReadLine(file->data[i], WR_FILE_LINE_MAX_LENGTH, fptr)) {
            TerminateFile(file);
            fclose(fptr);

            return false;
        }
    }

    fclose(fptr);

    return true;
}

void TerminateFile(WrFile* file) {
    if (!file) return;

    for (size_t i = 0; i < file->lineCount; i++) {
        free(file->data[i]);
    }

    free(file->data);

    file->lineCount = 0;
    file->data = NULL;
}

static size_t GetLineCount(FILE* fptr) {
    if (!fptr) return 0;

    size_t count = 0;
    int ch;

    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') count++;
    }

    rewind(fptr);

    return count;
}

static bool ReadLine(char* buff, int length, FILE* fptr) {
    if (!buff || !fptr) return false;

    if (!fgets(buff, length, fptr)) return false;

    return true;
}
