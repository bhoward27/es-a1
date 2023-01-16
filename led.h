#ifndef LED_H
#define LED_H

#include "int_typedefs.h"
#include <stdbool.h>

#define LED_FOLDER_PATH_PREFIX "/sys/class/leds/beaglebone:green:usr"
#define LED_TRIGGER_FILE_PATH_POSTFIX "/trigger"
#define LED_BRIGHTNESS_FILE_PATH_POSTFIX "/brightness"

typedef enum {
    LED_TOP = 0,
    LED_UPPER_MID,
    LED_LOWER_MID,
    LED_BOTTOM
} LedId;

typedef enum {
    LED_TRIGGER_FILE,
    LED_BRIGHTNESS_FILE
} LedFileType;

void Led_writeToFile(LedId led, LedFileType fileType, char* data);
void Led_init(void);

#endif