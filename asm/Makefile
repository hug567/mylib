

all:
	@nasm -f elf64 hello.asm
	@ld -d -o hello hello.o

clean:
	@rm -rf *.o *.img hello
