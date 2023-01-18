#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "int_typedefs.h"

#define OK 0
#define ERR_OPEN 1
#define ERR_WRITE 2
#define ERR_READ 3
#define ERR_CLOSE 4

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_CONFIG_PIN_PATH "/usr/bin/config-pin"

#define MAX_LOG_LEVEL_TAG_LEN 16
#define LOG_LEVEL_PATH "logLevel.txt"

#define DEFAULT_STRING_LEN 1024

// Citation: LOG and logMsg are inspired by
//      - https://stackoverflow.com/questions/8884335/print-the-file-name-line-number-and-function-name-of-a-calling-function-c-pro
//      - https://stackoverflow.com/questions/2849832/c-c-line-number
#define LOG(logLevel, format, ...) logMsg(logLevel, __FILE__, __LINE__, __func__, format __VA_OPT__(,) __VA_ARGS__);

#define DIE(format, ...) \
    LOG(LOG_LEVEL_ERROR, format __VA_OPT__(,) __VA_ARGS__); \
    exit(EXIT_FAILURE);

#define SYS_ERR(format, ...) \
    perror(__func__); \
    LOG(LOG_LEVEL_ERROR, format __VA_OPT__(,) __VA_ARGS__);

#define SYS_DIE(format, ...) \
    SYS_ERR(format __VA_OPT__(,) __VA_ARGS__); \
    exit(EXIT_FAILURE);

#define FILE_OPEN_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to open file '%s'.\n", fileName); \
    } \
    else { \
        SYS_ERR("Failed to open file '%s'.\n", fileName); \
    }

#define FILE_WRITE_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to write to file '%s'.\n", fileName); \
    } \
    else { \
        SYS_ERR("Failed to write to file '%s'.\n", fileName); \
    }

#define FILE_READ_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to read from file '%s'.\n", fileName); \
    } \
    else { \
        SYS_ERR("Failed to read from file '%s'.\n", fileName); \
    }

#define FILE_CLOSE_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to close file '%s'.\n", fileName); \
    } \
    else { \
        SYS_ERR("Failed to close file '%s'.\n", fileName); \
    }


typedef uint8 GpioNum;

typedef enum {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_WARN,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} LogLevel;

int writeToFile(char* fileName, char* data, bool exitOnFailure);
void runCommand(char* command);
int64 getTimeInMs(void);
void sleepForMs(int64 delayInMs);
void Gpio_exportPin(GpioNum pin, char* header);
void logMsg(LogLevel logLevel, char* file, int line, const char* function, const char* format, ...);
int initLogLevel(void);

#endif