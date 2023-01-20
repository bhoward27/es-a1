#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#define JOYSTICK_PRESSED 0
#define JOYSTICK_NOT_PRESSED 1

#define JOYSTICK_GPIO_HEADER "p8"

#define JOYSTICK_UP_LINUX_GPIO 26u
#define JOYSTICK_UP_GPIO 14u

#define JOYSTICK_DOWN_LINUX_GPIO 46u
#define JOYSTICK_DOWN_GPIO 16u

#define JOYSTICK_LEFT_LINUX_GPIO 65u
#define JOYSTICK_LEFT_GPIO 18u

#define JOYSTICK_RIGHT_LINUX_GPIO 47u
#define JOYSTICK_RIGHT_GPIO 15u

#define JOYSTICK_BUTTON_LINUX_GPIO 27u
#define JOYSTICK_BUTTON_GPIO 17u

#define JOYSTICK_NUM_PINS 5

typedef enum {
    JOYSTICK_INPUT_NONE = 0,
    JOYSTICK_INPUT_UP,
    JOYSTICK_INPUT_DOWN,
    JOYSTICK_INPUT_LEFT,
    JOYSTICK_INPUT_RIGHT,

    // This refers to when the joystick is pushed down towards the BeagleBone, like pressing a button.
    JOYSTICK_INPUT_BUTTON
} JoystickInputDirection;

// TODO: A struct might be nice. Could store header, gpio, linux GPIO, and JoystickInputDirection.

void Joystick_init(void);
JoystickInputDirection Joystick_readInput(void);

#endif