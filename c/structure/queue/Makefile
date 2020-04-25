CC=gcc
CFLAGS=-Wall -g
INCLUDE_PATH = -I../include

all:
	@echo ">>>> make list:"
	@echo "[01] make queue_char:          char queue"
	@echo "[02] make queue_int:           int queue"
	@echo "[03] make queue_struct:        struct queue"

queue_char:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} queue.c test_queue_char.c -o a.exe

queue_int:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} queue.c test_queue_int.c -o a.exe

queue_struct:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} queue.c test_queue_struct.c -o a.exe

clean:
	rm -rf *.o *.exe
