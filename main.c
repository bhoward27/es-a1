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
    printf("(Press left or right to exit.)\n\n");

    // Prepare randomness.
    int64 minMs = 500;
    int64 maxMs = 3000;
    FILE* pRngFile = fopen(URANDOM_PATH, "r");
    if (pRngFile == NULL) {
        FILE_OPEN_ERR(URANDOM_PATH, true);
    }

    // The game loop.
    bool keepRunning = true;
    while (keepRunning) {
        printf("Get ready...\n");

        // Wait random time between 0.5 s (500 ms) and 3 s (3000 ms).
        uint64 randWaitMs;
        size_t res = fread(&randWaitMs, sizeof(randWaitMs), 1, pRngFile);
        if (res == 0) {
            FILE_READ_ERR(URANDOM_PATH, true);
        }
        randWaitMs = randWaitMs % (maxMs - minMs) + minMs;
        LOG(LOG_LEVEL_DEBUG, "Sleeping %lld ms...\n", randWaitMs);
        sleepForMs(randWaitMs);

        JoystickInputDirection input = Joystick_readInput();
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

        // Pick a random direction (up or down) and print the direction.
        uint8 randDirectionNum = 0;
        size_t ret = fread(&randDirectionNum, sizeof(randDirectionNum), 1, pRngFile);
        if (ret == 0) {
            FILE_READ_ERR(URANDOM_PATH, true);
        }
        randDirectionNum %= 2; // Set to 0 or 1.

        JoystickInputDirection desiredDirection = JOYSTICK_INPUT_NONE;
        switch (randDirectionNum) {
            case 0:
                desiredDirection = JOYSTICK_INPUT_UP;
                printf("Press UP now!\n");
                break;
            case 1:
                desiredDirection = JOYSTICK_INPUT_DOWN;
                printf("Press DOWN now!\n");
                break;
            default:
                assert(false);
        }

        // TODO: Display the program's chosen direction on the BBG's LEDs:
        //      - Turn off the middle two LEDs
        Led_off(LED_UPPER_MID);
        Led_off(LED_LOWER_MID);
        switch (desiredDirection) {
            case JOYSTICK_INPUT_UP:
        //      - If program chose up, then turn on the top LED (#0)
                Led_on(LED_TOP);
                break;
            case JOYSTICK_INPUT_DOWN:
        //      - If program chose down, then turn on the bottom LED (#3)
                Led_on(LED_BOTTOM);
                break;
            default:
                assert(false);
                break;
        }

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

        // TODO: Remove this later.
        sleepForMs(1000);

        // Turn off whichever LED was on.
        switch (desiredDirection) {
            case JOYSTICK_INPUT_UP:
                Led_off(LED_TOP);
                break;
            case JOYSTICK_INPUT_DOWN:
                Led_off(LED_BOTTOM);
                break;
            default:
                assert(false);
                break;
        }

        printf("\n");
    }

    if (fclose(pRngFile)) {
        FILE_CLOSE_ERR(URANDOM_PATH, true);
    }

    return 0;
}