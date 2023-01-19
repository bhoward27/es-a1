#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "int_typedefs.h"
#include "led.h"
#include "joystick.h"
#include "utils.h"

#define URANDOM_PATH "/dev/urandom"

int main(int argc, char* args[])
{
    printf("Hello embedded world, from Ben!\n\n");
    initLogLevel();
    Led_init();
    Joystick_init();

    printf("\n");
    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit.)\n");

    // The game loop.
    // srandom(time(NULL));
    int64 minMs = 500;
    int64 maxMs = 3000;
    FILE* pFile = fopen(URANDOM_PATH, "r");
    if (pFile == NULL) {
        FILE_OPEN_ERR(URANDOM_PATH, true);
    }
    bool keepRunning = true;
    while (keepRunning) {
        printf("Get ready...\n");

        // Wait random time between 0.5 s (500 ms) and 3 s (3000 ms).

        // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
        uint64 randWaitMs;
        size_t res = fread(&randWaitMs, sizeof(uint64), 1, pFile);
        if (res == 0) {
            FILE_READ_ERR(URANDOM_PATH, true);
        }
        randWaitMs = randWaitMs % (maxMs - minMs) + minMs;
        //int64 randWaitMs = random() % (maxMs - minMs) + minMs;
        LOG(LOG_LEVEL_DEBUG, "Sleeping %lld ms...\n", randWaitMs);
        sleepForMs(randWaitMs);

        // TODO: If user is already pressing up or down, print "Too soon!" and continue / go to top of loop.
        JoystickInput input = Joystick_readInput();
        switch (input) {
            case JOYSTICK_INPUT_UP:
                // Fallthrough
            case JOYSTICK_INPUT_DOWN:
                printf("Too soon!\n");
                continue;
            case JOYSTICK_INPUT_LEFT:
                // Fallthrough
            case JOYSTICK_INPUT_RIGHT:
                // Fallthrough
            case JOYSTICK_INPUT_BUTTON:
                // Fallthrough
            case JOYSTICK_INPUT_NONE:
                break;
            default:
                assert(false);
                break;
        }

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

    if (fclose(pFile)) {
        FILE_CLOSE_ERR(URANDOM_PATH, true);
    }

    return 0;
}