CC = $(CROSS_COMPILE)gcc
CFLAGS=-Wall -g
LDFLAGS=-static
RM=rm -rf

OUTPUT=obj
TARGET=linux-test.elf
ALL_SRC=$(shell find . -path "./obj" -prune -o -name "*.c" -print)
ALL_OBJ=$(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(notdir $(ALL_SRC))))

define compile_src

	$(CC) $(CFLAGS) -c $(1) -o $(addprefix ./$(OUTPUT)/,$(patsubst %.c,%.o,$(notdir $(1))))
endef

link: compile
	$(CC) ${LDFLAGS} $(ALL_OBJ) -o ./$(OUTPUT)/$(TARGET)

compile:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
	$(foreach n, $(ALL_SRC), $(call compile_src, $(n)))

clean:
	${RM} ./$(OUTPUT)/

