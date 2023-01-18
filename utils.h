#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>

#include "int_typedefs.h"

#define ERR_OPEN 1
#define ERR_WRITE 2
#define OK 0

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_CONFIG_PIN_PATH "/usr/bin/config-pin"

typedef uint8 GpioNum;

int writeToFile(char* fileName, char* data, bool exitOnFailure);
void runCommand(char* command);
int64 getTimeInMs(void);
void sleepForMs(int64 delayInMs);
void Gpio_exportPin(GpioNum pin, char* header);

#endif