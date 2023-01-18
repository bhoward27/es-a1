#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#define JOYSTICK_PRESSED 0
#define JOYSTICK_NOT_PRESSED 1

#define JOYSTICK_GPIO_HEADER "p8"

#define JOYSTICK_UP_GPIO 26u
#define JOYSTICK_DOWN_GPIO 46u
#define JOYSTICK_LEFT_GPIO 65u
#define JOYSTICK_RIGHT_GPIO 47u
#define JOYSTICK_BUTTON_GPIO 27u

typedef enum {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,

    // This refers to when the joystick is pushed down towards the BeagleBone, like pressing a button.
    BUTTON
} JoystickInput;

void Joystick_init(void);

#endif