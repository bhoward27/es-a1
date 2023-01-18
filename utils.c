#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>

#include "utils.h"

int writeToFile(char* fileName, char* data, bool exitOnFailure)
{
    assert(fileName != NULL);
    assert(data != NULL);

    FILE* pFile = fopen(fileName, "w");
    if (pFile == NULL) {
        if (exitOnFailure) {
            printf("ERROR: Failed to open file '%s' in writeToFile().\n", fileName);
            exit(1);
        }
        return ERR_OPEN;
    }
    int res = fprintf(pFile, data);
    if (res <= 0) {
        if (exitOnFailure) {
            printf("ERROR: Failed to write to file '%s' in writeToFile().\n", fileName);
            exit(1);
        }
        return ERR_WRITE;
    }

    fclose(pFile);
    return OK;
}

void runCommand(char* command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
        // printf("--> %s", buffer);  // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf("  command:   %s\n", command);
        printf("  exit code: %d\n", exitCode);
    }
}

int64 getTimeInMs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    int64 seconds = spec.tv_sec;
    int64 nanoSeconds = spec.tv_nsec;
    int64 milliSeconds = seconds * 1000
                 + nanoSeconds / 1000000;
    return milliSeconds;
}

void sleepForMs(int64 delayInMs)
{
    const int64 NS_PER_MS = 1000 * 1000;
    const int64 NS_PER_SECOND = 1000000000;
    int64 delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

void Gpio_exportPin(GpioNum pin, char* header)
{
    // Set pin to GPIO mode.
    char pinString[4];
    snprintf(pinString, 4, "%u", pin);
    char command[1024];
    snprintf(command, 1024, "%s %s.%s gpio", GPIO_CONFIG_PIN_PATH, header, pinString);
    runCommand(command);

    // Export the pin.
    writeToFile(GPIO_EXPORT_PATH, pinString, true);
}