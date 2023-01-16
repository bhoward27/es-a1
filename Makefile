MAIN_FILE = react_game
OUT_DIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -std=c11 -D _POSIX_C_SOURCE=200809L -g -Wall -Werror -Wshadow -Wno-error=unused-variable -Wno-error=unused-function

app: $(MAIN_FILE).c
	$(CC_C) $(CFLAGS) $(MAIN_FILE).c -o $(OUT_DIR)/$(MAIN_FILE)

all: app

clean:
	rm $(OUT_DIR)/$(MAIN_FILE)