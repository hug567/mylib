CC=gcc
CFLAGS=-Wall -g

RM=rm -rf

ALL_SRC=$(shell find . -path "./obj" -prune -o -name "*.c" -print)

all:
	${CC} ${CFLAGS} ${ALL_SRC} -o a.exe

clean:
	${RM} *.o *.exe *.elf

