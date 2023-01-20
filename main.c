#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#include "int_typedefs.h"
#include "led.h"
#include "joystick.h"
#include "utils.h"

#define URANDOM_PATH "/dev/urandom"
#define MAX_WAIT_TIME_MS 5000

int main(int argc, char* args[])
{
    printf("Hello embedded world, from Ben!\n\n");
    initLogLevel();
    Led_init();
    Led_allOff();
    Joystick_init();

    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit.)\n\n");

    // Prepare randomness.
    int64 minMs = 500;
    int64 maxMs = 3000;
    FILE* pRngFile = fopen(URANDOM_PATH, "r");
    if (pRngFile == NULL) {
        FILE_OPEN_ERR(URANDOM_PATH, true);
    }

    int64 fastestResponseTime = LONG_MAX;

    // The game loop.
    bool keepPlaying = true;
    while (keepPlaying) {
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

        // Read player's input now to prevent cheating.
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

        // Pick a random direction that the player will need to input.
        uint8 randDirectionNum = 0;
        size_t ret = fread(&randDirectionNum, sizeof(randDirectionNum), 1, pRngFile);
        if (ret == 0) {
            FILE_READ_ERR(URANDOM_PATH, true);
        }
        randDirectionNum %= 2; // Set to 0 or 1.
        JoystickInputDirection requiredDirection = JOYSTICK_INPUT_NONE;
        switch (randDirectionNum) {
            case 0:
                requiredDirection = JOYSTICK_INPUT_UP;
                printf("Press UP now!\n");
                break;
            case 1:
                requiredDirection = JOYSTICK_INPUT_DOWN;
                printf("Press DOWN now!\n");
                break;
            default:
                assert(false);
        }

        // Display the program's chosen direction on the BBG's LEDs:
        switch (requiredDirection) {
            case JOYSTICK_INPUT_UP:
                Led_on(LED_TOP);
                break;
            case JOYSTICK_INPUT_DOWN:
                Led_on(LED_BOTTOM);
                break;
            default:
                assert(false);
                break;
        }

        // Time how long it takes the user to press the joystick in any direction.
        // (Pressing the joystick down like a button doesn't count).
        int64 startTime = getTimeInMs();
        int64 inputTime;
        int64 responseTime;
        JoystickInputDirection joystickInput = JOYSTICK_INPUT_NONE;
        // TODO: Ideally would use a blocking call version of Joystick_readInput() here to not waste CPU.
        do {
            joystickInput = Joystick_readInput();
            inputTime = getTimeInMs();
            responseTime = inputTime - startTime;
        } while (
            (joystickInput == JOYSTICK_INPUT_NONE || joystickInput == JOYSTICK_INPUT_BUTTON)
            &&
            responseTime <= MAX_WAIT_TIME_MS
        );

        // Respond to player's input.
        if (responseTime > MAX_WAIT_TIME_MS) {
            printf("Quitting -- no input within %d seconds.\n", MAX_WAIT_TIME_MS / 1000);
            keepPlaying = false;
        }
        else if (joystickInput == requiredDirection) {
            printf("Correct!\n");
            if (responseTime < fastestResponseTime) {
                fastestResponseTime = responseTime;
                printf("NEW BEST TIME!\n");
            }
            printf("Your reaction time was %lld ms; best time so far is %lld ms.\n", responseTime, fastestResponseTime);
            uint64 numCycles = Led_flashAllLeds(4, NUM_MS_PER_S/2);
            LOG(LOG_LEVEL_DEBUG, "Flashed on and off %llu times.\n", numCycles);
        }
        // If player's input was incorrect and up or down.
        else if (joystickInput == JOYSTICK_INPUT_UP || joystickInput == JOYSTICK_INPUT_DOWN) {
            printf("Incorrect.\n");
            uint64 numCycles = Led_flashAllLeds(10, NUM_MS_PER_S);
            LOG(LOG_LEVEL_DEBUG, "Flashed on and off %llu times.\n", numCycles);
        }
        else if (joystickInput == JOYSTICK_INPUT_LEFT || joystickInput == JOYSTICK_INPUT_RIGHT) {
            printf("Quitting now, on the player's request.\n");
            keepPlaying = false;
        }

        // Just in case any were on.
        Led_allOff();

        printf("\n");
    }

    if (fclose(pRngFile)) {
        FILE_CLOSE_ERR(URANDOM_PATH, true);
    }

    LOG(LOG_LEVEL_INFO, "Reached end of program successfully.\n");
    return 0;
}