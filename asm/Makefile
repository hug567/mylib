
CC = gcc
CFLAGS =
LD = ld
LDFLAGS =
LIB = -lc
OBJ = hello_asm.o hello_c.o

all:
	@nasm -f elf64 -o hello_asm.o hello_asm.s
	@$(CC) -c hello_c.c
	@$(LD) -d -o hello.elf $(OBJ) $(LIB)

clean:
	@rm -rf *.o *.img *.elf
