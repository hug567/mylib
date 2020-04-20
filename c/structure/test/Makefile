CC=gcc
CFLAGS=-Wall -g
INCLUDE_PATH = -I../include

all:
	@echo ">>>> make list:"
	@echo "[01] make stack_int:           int link tree"
	@echo "[02] make stack_char:          char link tree"
	@echo "[03] make stack_struct:        struct link tree"

stack_int:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} stack.c test_stack_int.c -o a.exe

stack_char:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} stack.c test_stack_char.c -o a.exe

stack_struct:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} stack.c test_stack_struct.c -o a.exe

clean:
	rm -rf *.o *.exe
