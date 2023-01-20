#include "joystick.h"
#include "utils.h"

void Joystick_init(void) {
    bool isInput = true;
    LOG(LOG_LEVEL_DEBUG, "Calling Gpio_initPin()...\n");
    Gpio_initPin((GpioNum) JOYSTICK_UP_GPIO, JOYSTICK_GPIO_HEADER, JOYSTICK_UP_LINUX_GPIO, isInput);

    LOG(LOG_LEVEL_DEBUG, "Calling Gpio_initPin()...\n");
    Gpio_initPin((GpioNum) JOYSTICK_DOWN_GPIO, JOYSTICK_GPIO_HEADER, JOYSTICK_DOWN_LINUX_GPIO, isInput);

    // TODO: Shouldn't need to comment these out :/.
    LOG(LOG_LEVEL_DEBUG, "Calling Gpio_initPin()...\n");
    Gpio_initPin((GpioNum) JOYSTICK_LEFT_GPIO, JOYSTICK_GPIO_HEADER, JOYSTICK_LEFT_LINUX_GPIO, isInput);
    LOG(LOG_LEVEL_DEBUG, "Calling Gpio_initPin()...\n");
    Gpio_initPin((GpioNum) JOYSTICK_RIGHT_GPIO, JOYSTICK_GPIO_HEADER, JOYSTICK_RIGHT_LINUX_GPIO, isInput);


    LOG(LOG_LEVEL_DEBUG, "Calling Gpio_initPin()...\n");
    Gpio_initPin((GpioNum) JOYSTICK_BUTTON_GPIO, JOYSTICK_GPIO_HEADER, JOYSTICK_BUTTON_LINUX_GPIO, isInput);
}

JoystickInputDirection Joystick_readInput(void)
{
    // TODO: Should be a constant array somewhere.
    GpioNum gpios[JOYSTICK_NUM_PINS] = {
        JOYSTICK_UP_LINUX_GPIO,
        JOYSTICK_DOWN_LINUX_GPIO,
        JOYSTICK_LEFT_LINUX_GPIO,
        JOYSTICK_RIGHT_LINUX_GPIO,
        JOYSTICK_BUTTON_LINUX_GPIO
    };
    //int inputs[JOYSTICK_NUM_PINS] = {GPIO_READ_ERR};
    uint8 numPressed = 0;
    JoystickInputDirection input = JOYSTICK_INPUT_NONE;
    for (int i = 0; i < JOYSTICK_NUM_PINS && numPressed <= 1; i++) {
        // inputs[i] = Gpio_readInput(gpios[i]);
        GpioNum gpio = gpios[i];
        int gpioInput = Gpio_readInput(gpio);
        switch (gpioInput) {
            case GPIO_READ_ERR:
                LOG(LOG_LEVEL_ERROR, "Gpio_readInput(%u) failed.\n", gpio);
                break;
            case JOYSTICK_PRESSED:
                LOG(LOG_LEVEL_DEBUG, "GPIO pin #%u was pressed.\n", gpio);
                numPressed++;
                switch (gpio) {
                    case JOYSTICK_UP_LINUX_GPIO:
                        // TODO: Perhaps there shouldn't be this JoystickInputDirection type at all? Just use the GPIO defines?
                        input = JOYSTICK_INPUT_UP;
                        break;
                    case JOYSTICK_DOWN_LINUX_GPIO:
                        input = JOYSTICK_INPUT_DOWN;
                        break;
                    case JOYSTICK_LEFT_LINUX_GPIO:
                        input = JOYSTICK_INPUT_LEFT;
                        break;
                    case JOYSTICK_RIGHT_LINUX_GPIO:
                        input = JOYSTICK_INPUT_RIGHT;
                        break;
                    case JOYSTICK_BUTTON_LINUX_GPIO:
                        input = JOYSTICK_INPUT_BUTTON;
                        break;
                    default:
                        assert(false);
                        break;
                }
                break;
            case JOYSTICK_NOT_PRESSED:
                break;
            default:
                assert(false);
                break;
        }
    }

    if (numPressed > 1) {
        input = JOYSTICK_INPUT_NONE;
    }
    LOG(LOG_LEVEL_DEBUG, "Final joystick input = %u.\n", input);

    return input;
}