#include "led.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void Led_overwriteFile(LedId led, LedFileType fileType, char* data)
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

    overwriteFile(fileName, data, true);
}

void Led_init(void)
{
    Led_overwriteFile(LED_TOP, LED_TRIGGER_FILE, "none");
    Led_overwriteFile(LED_UPPER_MID, LED_TRIGGER_FILE, "none");
    Led_overwriteFile(LED_LOWER_MID, LED_TRIGGER_FILE, "none");
    Led_overwriteFile(LED_BOTTOM, LED_TRIGGER_FILE, "none");
}

void Led_on(LedId led)
{
    Led_overwriteFile(led, LED_BRIGHTNESS_FILE, LED_ON);
}

void Led_off(LedId led)
{
    Led_overwriteFile(led, LED_BRIGHTNESS_FILE, LED_OFF);
}

uint64 Led_flashAllLeds(uint32 frequencyHz, int64 durationMs)
{
    int64 period = NUM_MS_PER_S / frequencyHz;
    int64 timeGap = period / 2;
    int64 startTime = getTimeInMs();
    int64 maxEndTime = startTime + durationMs;
    int64 nextIterationTime = startTime + period;
    uint64 numCycles = 0;
    while (nextIterationTime <= maxEndTime) {
        Led_allOn();
        sleepForMs(timeGap);

        Led_allOff();
        sleepForMs(timeGap);

        nextIterationTime += period;
        numCycles++;
    }
    return numCycles;
}

void Led_allOn(void)
{
    Led_on(LED_TOP);
    Led_on(LED_UPPER_MID);
    Led_on(LED_LOWER_MID);
    Led_on(LED_BOTTOM);
}

void Led_allOff(void)
{
    Led_off(LED_TOP);
    Led_off(LED_UPPER_MID);
    Led_off(LED_LOWER_MID);
    Led_off(LED_BOTTOM);
}