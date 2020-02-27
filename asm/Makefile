
CC = gcc
CFLAGS = -static
LD = ld
LDFLAGS =
LIB =
OBJ = hello_asm.o #hello_c.o

all:
	@nasm -f elf64 -o hello_asm.o hello_asm.asm
	@$(CC) $(CFLAGS) -c hello_c.c
	@$(LD) -s -o hello.elf $(OBJ) $(LIB)

clean:
	@rm -rf *.o *.img *.elf
