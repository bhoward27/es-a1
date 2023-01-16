#ifndef LED_H
#define LED_H

#include "int_typedefs.h"
#include <stdbool.h>

#define LED_FOLDER_PATH_PREFIX "/sys/class/leds/beaglebone:green:usr"
#define LED_TRIGGER_FILE_PATH_POSTFIX "/trigger"
#define LED_BRIGHTNESS_FILE_PATH_POSTFIX "/brightness"

typedef enum {
    TOP = 0,
    UPPER_MID,
    LOWER_MID,
    BOTTOM
} LedId;

typedef enum {
    TRIGGER,
    BRIGHTNESS
} LedFileType;

void Led_writeToFile(LedId led, LedFileType fileType, char* data);

#endif