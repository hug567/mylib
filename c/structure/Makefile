srctree = .
CC = gcc
CFLAGS := -Wall -g
LIBS := -lm
OS_TYPE = $(shell uname)

test:
	@echo "OS type is: $(OS_TYPE)"

bstree:
	@$(CC) $(CFLAGS) $(LIBS) bstree.c

heap:
	@$(CC) $(CFLAGS) $(LIBS) heap.c

list:
	@$(CC) $(CFLAGS) $(LIBS) list.c

queue:
	@$(CC) $(CFLAGS) $(LIBS) queue.c

stack:
	@$(CC) $(CFLAGS) $(LIBS) stack.c

tree:
	@$(CC) $(CFLAGS) $(LIBS) tree.c

graph:
	@$(CC) $(CFLAGS) $(LIBS) graph.c

graph2:
	@$(CC) $(CFLAGS) $(LIBS) graph2.c

.PHONY: clean
clean:
	@rm -rf  *.o *.out
