CC=gcc
CFLAGS=-Wall -g
INCLUDE_PATH = -I../include

all:
	@echo "You can make the flowing golas:"
	@echo "[01] make btree:           binary tree"

btree:
	${CC} ${CFLAGS}  ${INCLUDE_PATH} tree.c ../stack/stack.c test_btree.c -o a.exe

clean:
	rm -rf *.o *.exe
