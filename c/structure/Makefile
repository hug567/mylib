
CC = gcc
CFLAGS := -Wall -g
LIBS := -lm

default:
	@echo "data structure practice"

bstree:
	@$(CC) $(CFLAGS) bstree.c -o bstree.out

heap:
	@$(CC) $(CFLAGS) heap.c -o heap.out

list:
	@$(CC) $(CFLAGS) list.c -o list.out

queue:
	@$(CC) $(CFLAGS) queue.c -o queue.out

stack:
	@$(CC) $(CFLAGS) stack.c -o stack.out

tree:
	@$(CC) $(CFLAGS) tree.c -o tree.out

.PHONY: clean
clean:
	@rm -rf  *.o *.out
