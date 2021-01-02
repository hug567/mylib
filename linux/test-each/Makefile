CC=gcc
CFLAGS=-Wall -g
BUILD_DIR=mybuild
SRC=main.c get_termios.c

prepare:
	rm -rf $(BUILD_DIR)
	mkdir $(BUILD_DIR)
	cp -r `ls | grep -v $(BUILD_DIR)` $(BUILD_DIR)
	make -C $(BUILD_DIR) -f Makefile all

all:
	$(CC) $(CFLAGS) ${SRC} -o tty_debug.elf

clean:
	rm -rf $(BUILD_DIR)
