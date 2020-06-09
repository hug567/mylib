CC = $(CROSS_COMPILE)gcc
CFLAGS=-Wall -g
LDFLAGS=-static
RM=rm -rf

OUTPUT=obj
TARGET=test-libc.elf

ALL_SRC=$(shell find . -path "./obj" -prune -o -name "*.c" -print)
ALL_OBJ_DIR=$(subst ./,./$(OUTPUT)/,$(dir $(ALL_SRC)))
ALL_OBJ=$(subst ./,./$(OUTPUT)/,$(patsubst %.c,%.o,$(ALL_SRC)))

define create_dir

	@if [ ! -d $(1) ]; then mkdir -p $(1); fi
endef

define compile_src

	$(CC) $(CFLAGS) -c $(1) -o $(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(1)))
endef

all: link

link: compile
	$(CC) ${LDFLAGS} $(ALL_OBJ) -o ./$(OUTPUT)/$(TARGET)

compile:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
	$(foreach n, $(ALL_OBJ_DIR), $(call create_dir, $(n)))
	$(foreach n, $(ALL_SRC), $(call compile_src, $(n)))

clean:
	${RM} ./$(OUTPUT)/
