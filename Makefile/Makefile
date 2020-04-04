CC = gcc
LD = ld
MAKE = make
RM = rm -rf

CFLAGS = -Wall -O2
LDFLAGS :=
LIBS :=
LIB_PATH :=
INCLUDE_PATH := -I./include

export CC LD MAKE CGLAGS

SUB_DIRS = subdir

all: subdirs
	# 生成.o文件
	$(CC) ${CFLAGS} ${INCLUDE_PATH} -c main.c test01.c
	# 链接输出可执行文件
	${CC} -o main.elf main.o test01.o

subdirs:
	echo "Will compile *.c in subdirs"
	${MAKE} -C ${SUB_DIRS}

.PHONY:clean
clean:
	${RM} *.o *.elf
