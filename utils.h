#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "int_typedefs.h"

#define GPIO_READ_ERR -1
#define OK 0
#define ERR_OPEN 1
#define ERR_WRITE 2
#define ERR_READ 3
#define ERR_CLOSE 4

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_PIN_PATH_PREFIX "/sys/class/gpio/gpio"
#define GPIO_CONFIG_PIN_PATH "/usr/bin/config-pin"

#define MAX_LOG_LEVEL_TAG_LEN 16
#define LOG_LEVEL_PATH "logLevel.txt"

#define DEFAULT_STRING_LEN 1024

typedef enum {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_WARN,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} LogLevel;

// TODO: BAD.
extern uint8 gLogLevel;

// Citation: LOG and logMsg are inspired by
//      - https://stackoverflow.com/questions/8884335/print-the-file-name-line-number-and-function-name-of-a-calling-function-c-pro
//      - https://stackoverflow.com/questions/2849832/c-c-line-number
//      - https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
#define LOG(logLevel, format, ...) logMsg(logLevel, __FILE__, __LINE__, __func__, format __VA_OPT__(,) __VA_ARGS__);

#define DIE(format, ...) \
    LOG(LOG_LEVEL_ERROR, format __VA_OPT__(,) __VA_ARGS__); \
    exit(EXIT_FAILURE);

#define SYS_WARN(format, ...) \
    char err[DEFAULT_STRING_LEN]; \
    snprintf(err, DEFAULT_STRING_LEN, "%s (errno = %d)", __func__, errno); \
    if (gLogLevel >= LOG_LEVEL_WARN) \
        perror(err); \
    LOG(LOG_LEVEL_WARN, format __VA_OPT__(,) __VA_ARGS__);

#define SYS_DIE(format, ...) \
    SYS_WARN(format __VA_OPT__(,) __VA_ARGS__); \
    exit(EXIT_FAILURE);

#define FILE_OPEN_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to open file '%s'.\n", fileName, errno); \
    } \
    else { \
        SYS_WARN("Failed to open file '%s'.\n", fileName, errno); \
    }

#define FILE_WRITE_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to write to file '%s'.\n", fileName); \
    } \
    else { \
        SYS_WARN("Failed to write to file '%s'.\n", fileName); \
    }

#define FILE_READ_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to read from file '%s'.\n", fileName); \
    } \
    else { \
        SYS_WARN("Failed to read from file '%s'.\n", fileName); \
    }

#define FILE_CLOSE_ERR(fileName, die) \
    assert(fileName != NULL); \
    if (die) { \
        SYS_DIE("Failed to close file '%s'.\n", fileName); \
    } \
    else { \
        SYS_WARN("Failed to close file '%s'.\n", fileName); \
    }


typedef uint8 GpioNum;


int overwriteFile(char* filePath, char* string, bool exitOnFailure);
int readFile(char* filePath, void* outData, size_t numBytesPerItem, size_t numItems, bool exitOnFailure);
int runCommand(char* command);
int64 getTimeInMs(void);
void sleepForMs(int64 delayInMs);
void Gpio_exportPin(GpioNum pin, char* header, GpioNum linuxPin);
void Gpio_configIo(GpioNum linuxPin, bool isInput);
void Gpio_initPin(GpioNum pin, char* header, GpioNum linuxPin, bool isInput);
int Gpio_readInput(GpioNum linuxPin);
void logMsg(LogLevel logLevel, char* file, int line, const char* function, const char* format, ...);
int initLogLevel(void);

#endif