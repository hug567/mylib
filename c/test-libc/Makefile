CC=gcc
CFLAGS=-Wall -g

RM=rm -rf

OUTPOT=obj

ALL_SRC=$(shell find . -path "./obj" -prune -o -name "*.c" -print)

define compile_src
	echo -e "src = ${1}\n"
endef

all:
	echo "start Makefile"
	@$(foreach n, $(ALL_SRC), $(call compile_src, ${n}))

debug:
	#@echo "ALL_SRC = ${ALL_SRC}"
	#${CC} ${CFLAGS} ${ALL_SRC} -o a.exe
	#${CC} ${CFLAGS} ${ALL_SRC} -o ./${OUTPUT}/${0}.o

clean:
	${RM} *.o *.exe *.elf

