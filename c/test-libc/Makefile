CC=gcc
CFLAGS=-Wall -g

RM=rm -rf

ALL_SRC=$(shell find . -name "*.c")

all:
	${CC} ${CFLAGS} ${ALL_SRC} -o a.exe

clean:
	${RM} *.o *.exe *.elf

