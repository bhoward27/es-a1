#include "led.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void Led_writeToFile(LedId led, LedFileType fileType, char* data)
{
    // Prepare the file name.
    char fileName[DEFAULT_STRING_LEN];
    char postfix[512];
    switch (fileType) {
        case LED_TRIGGER_FILE:
            // char *strncpy(char *dest, const char *src, size_t n);
            strncpy(postfix, LED_TRIGGER_PATH_POSTFIX, 512);
            break;
        case LED_BRIGHTNESS_FILE:
            strncpy(postfix, LED_BRIGHTNESS_PATH_POSTFIX, 512);
            break;
        default:
            // Unexpected LedFileType.
            assert(false);
            break;
    }
    //  int snprintf(char *str, size_t size, const char *format, ...);
    snprintf(fileName, DEFAULT_STRING_LEN, "%s%d%s", LED_FOLDER_PATH_PREFIX, led, postfix);

    writeToFile(fileName, data, true);
}

void Led_init(void)
{
    Led_writeToFile(LED_TOP, LED_TRIGGER_FILE, "none");
    Led_writeToFile(LED_UPPER_MID, LED_TRIGGER_FILE, "none");
    Led_writeToFile(LED_LOWER_MID, LED_TRIGGER_FILE, "none");
    Led_writeToFile(LED_BOTTOM, LED_TRIGGER_FILE, "none");
}
