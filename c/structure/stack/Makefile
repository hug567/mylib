CC=gcc
CFLAGS=-Wall -g
INCLUDE_PATH = -I../include

all:
	@echo ">>>> make list:"
	@echo "[01] make stack:           link tree"

stack:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} stack.c test_stack.c -o a.exe

clean:
	rm -rf *.o *.exe
