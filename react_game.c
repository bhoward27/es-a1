#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/wait.h>

#include "int_typedefs.h"
#include "led.h"

typedef enum {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
} JoystickDirection;

void runCommand(char* command);
int64 getTimeInMs(void);
void sleepForMs(int64 delayInMs);

int main(int argc, char* args[])
{
    printf("Hello embedded world, from Ben!\n");

    // TODO: Set up / initialize LEDs and joystick.
    // Set each LEDs' trigger to none.

    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit.)\n");

    // The game loop.
    bool keepRunning = true;
    while (keepRunning) {
        printf("Get ready...\n");

        // TODO: Wait random time between 0.5s and 3s.

        // TODO: If user is already pressing up or down, print "Too soon!" and continue / go to top of loop.

        // TODO: Pick a random direction (up or down) and print the direction.

        // TODO: Display the program's chosen direction on the BBG's LEDs:
        //      - Turn off the middle two LEDs
        //      - If program chose up, then turn on the top LED (#0)
        //      - If program chose down, then turn on the bottom LED (#3)

        // TODO: Time how long it takes the user to press the joystick in any direction.
        //      - If time > 5 seconds, exit program with a message without waiting for a joystick press:
        //      "Quitting -- no input within five seconds."

        // TODO: Process the user's joystick press:
        //      a) If the user pressed up or down corectly, then:
        //          - Print a message
        //          - If this was the fastest correct response time yet, display that in a message
        //          - Display this attempt's response time, and the high score, in milliseconds
        //          - Flash all four LEDs on and off at 4 Hz for 0.5 seconds (two flashes)
        //      b) If the user pressed up or down incorrectly, print a message and flash all four LEDs on and off
        //          at 10 Hz for 1 second.
        //      c) If the user pressed left or right, print a message and quit.

    }

    return 0;
}

// Citation: Function copied from Dr. Fraser's CMPT 433 documents.
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

// Citation: Function copied from Dr. Fraser's CMPT 433 documents.
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

// Citation: Function copied from Dr. Fraser's CMPT 433 documents.
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