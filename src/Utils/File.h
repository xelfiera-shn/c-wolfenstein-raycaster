#ifndef WR_FILE_H
#define WR_FILE_H

#include <stdlib.h>
#include <stdbool.h>

#define WR_FILE_LINE_MAX_LENGTH 256

typedef struct WrFile {
    size_t lineCount;
    char** data;
} WrFile;

bool InitFile(WrFile* file, const char* path);
void TerminateFile(WrFile* file);

#endif // WR_FILE_H
