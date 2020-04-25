CC=gcc
CFLAGS=-Wall -g

RM=rm -rf

OUTPUT=obj

ALL_SRC=$(shell find . -path "./obj" -prune -o -name "*.c" -print)

define compile_src
	$(info para = $(1))
	$(info src = $(notdir $(1)))
	$(info obj = $(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(notdir $(1)))))
	obj=$(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(notdir $(1))))
	$(info obj = $(obj))
	$(CC) $(CFLAGS) -c $(1) -o $(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(notdir $(1))))
endef

debug:
	echo "start Makefile"

compile:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
	$(foreach n, $(ALL_SRC), $(call compile_src, $(n)))

link: compile

test:

	#@echo "ALL_SRC = ${ALL_SRC}"
	#${CC} ${CFLAGS} ${ALL_SRC} -o a.exe
	#${CC} ${CFLAGS} ${ALL_SRC} -o ./${OUTPUT}/${0}.o

clean:
	${RM} *.o *.exe *.elf

