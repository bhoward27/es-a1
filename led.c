#include "led.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Will have to move this or change overall division of files.
#define ERR_OPEN 1
#define ERR_WRITE 2
#define OK 0

// TODO: Will have to move this or change overall division of files.
int writeToFile(char* fileName, char* data)
{
    assert(fileName != NULL);
    assert(data != NULL);

    FILE* pFile = fopen(fileName, "w");
    if (pFile == NULL) {
        return ERR_OPEN;
    }
    int res = fprintf(pFile, data);
    if (res <= 0) {
        return ERR_WRITE;
    }

    fclose(pFile);
    return OK;
}

void Led_writeToFile(LedId led, LedFileType fileType, char* data)
{
    // Prepare the file name.
    char fileName[1024];
    char postfix[512];
    switch (fileType) {
        case LED_TRIGGER_FILE:
            // char *strncpy(char *dest, const char *src, size_t n);
            strncpy(postfix, LED_TRIGGER_FILE_PATH_POSTFIX, 512);
            break;
        case LED_BRIGHTNESS_FILE:
            strncpy(postfix, LED_BRIGHTNESS_FILE_PATH_POSTFIX, 512);
            break;
        default:
            // Unexpected LedFileType.
            assert(true);
            break;
    }
    //  int snprintf(char *str, size_t size, const char *format, ...);
    snprintf(fileName, 1024, "%s%d%s", LED_FOLDER_PATH_PREFIX, led, postfix);

    writeToFile(fileName, data);
}

void Led_init(void)
{
    Led_writeToFile(LED_TOP, LED_TRIGGER_FILE, "none");
    Led_writeToFile(LED_UPPER_MID, LED_TRIGGER_FILE, "none");
    Led_writeToFile(LED_LOWER_MID, LED_TRIGGER_FILE, "none");
    Led_writeToFile(LED_BOTTOM, LED_TRIGGER_FILE, "none");
}
