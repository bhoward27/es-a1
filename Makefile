OUT_DIR = $(HOME)/cmpt433/public/myApps
LOG_LEVEL_FILE=$(OUT_DIR)/logLevel.txt

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -std=gnu11 -D _POSIX_C_SOURCE=200809L -g -Wall -Werror -Wshadow -Wno-error=unused-variable -Wno-error=unused-function
OFLAGS = $(CFLAGS) -c

OBJS = main.o utils.o led.o joystick.o

all: reactGame

reactGame: $(OBJS)
	$(CC_C) $(CFLAGS) $(OBJS) -o $(OUT_DIR)/reactGame

# Makes new log level file if it doesn't exist.
	./makeLogLevelFile.sh $(LOG_LEVEL_FILE)

main.o: main.c utils.o led.o joystick.o
	$(CC_C) $(OFLAGS) main.c

utils.o: utils.c utils.h
	$(CC_C) $(OFLAGS) utils.c

led.o: led.c led.h
	$(CC_C) $(OFLAGS) led.c

joystick.o: joystick.c joystick.h
	$(CC_C) $(OFLAGS) joystick.c

clean:
	rm -f $(OUT_DIR)/reactGame
	rm -f *.o *.s *.out

clean-log:
	rm -f $(LOG_LEVEL_FILE)