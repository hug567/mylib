CC=gcc
CFLAGS=-Wall -g
RM=rm -rf

OUTPUT=obj
ALL_SRC=$(shell find . -path "./obj" -prune -o -name "*.c" -print)
ALL_OBJ=$(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(notdir $(ALL_SRC))))

define compile_src
	$(info $(obj))
	$(CC) $(CFLAGS) -c $(1) -o $(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(notdir $(1))))
endef

link: compile
	$(CC) $(ALL_OBJ) -o ./$(OUTPUT)/test-libc.elf

compile:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
	$(foreach n, $(ALL_SRC), $(call compile_src, $(n)))

clean:
	${RM} ./$(OUTPUT)/

