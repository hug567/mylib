# run: make -f file.mk

all:
	echo "hello makefile"

CROSS_COMPILE="arm-none-linux-gnueabi-"
gcc_dir=$(dir $(shell which $(CROSS_COMPILE)gcc))
compiler_lib="$(shell cd $(gcc_dir)/..; pwd)/arm-none-linux-gnueabi/libc/usr"

compiler_libs_dir="${compiler_lib}/lib"
compiler_headers_dir="${compiler_lib}/include"

find_lib:
	@echo "gcc_dir = $(gcc_dir)"
	@echo "compiler_libs_dir = $(compiler_libs_dir)"
	@echo "compiler_headers_dir = $(compiler_headers_dir)"
