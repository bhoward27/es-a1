#include "joystick.h"
#include "utils.h"

void Joystick_init(void) {
    LOG( LOG_LEVEL_DEBUG, "Calling Gpio_exportPin()...\n");
    Gpio_exportPin((GpioNum) JOYSTICK_UP_GPIO, JOYSTICK_GPIO_HEADER);

    LOG( LOG_LEVEL_DEBUG, "Calling Gpio_exportPin()...\n");
    Gpio_exportPin((GpioNum) JOYSTICK_DOWN_GPIO, JOYSTICK_GPIO_HEADER);

    LOG( LOG_LEVEL_DEBUG, "Calling Gpio_exportPin()...\n");
    Gpio_exportPin((GpioNum) JOYSTICK_LEFT_GPIO, JOYSTICK_GPIO_HEADER);

    LOG( LOG_LEVEL_DEBUG, "Calling Gpio_exportPin()...\n");
    Gpio_exportPin((GpioNum) JOYSTICK_RIGHT_GPIO, JOYSTICK_GPIO_HEADER);

    LOG( LOG_LEVEL_DEBUG, "Calling Gpio_exportPin()...\n");
    Gpio_exportPin((GpioNum) JOYSTICK_BUTTON_GPIO, JOYSTICK_GPIO_HEADER);
}