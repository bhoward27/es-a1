#include <stdio.h>
#include <stdbool.h>

#include "int_typedefs.h"
#include "led.h"
#include "joystick.h"

int main(int argc, char* args[])
{
    printf("Hello embedded world, from Ben!\n");

    // TODO: Set up / initialize LEDs and joystick.
    // Set each LEDs' trigger to none.
    Led_init();

    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit.)\n");

    // The game loop.
    // bool keepRunning = true;
    // while (keepRunning) {
    //     printf("Get ready...\n");

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

    // }

    return 0;
}