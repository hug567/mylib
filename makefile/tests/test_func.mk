# leauning makefile function
# run: make -f file.mk
# 2023.05.18

# define function, no args, no return
define test_print
	@echo "$(0): ------------------------------------------"
	@echo "hello makefile"
endef

# function with args
define test_args
	@echo "$(0): ------------------------------------------"
	@echo "name: [$(1)], age: [$(2)]"
endef

# function with return value
define test_add
$(shell expr $(1) + $(2))
endef

# function call with return value
sum := $(call test_add,3,6)

all:
	@# function call
	$(call test_print)
	@# function call with args
	$(call test_args,Bob,18)
	@# function call with return value
	@echo "sum: $(sum)"
	@echo "4 + 6 = $(call test_add,4,6)"
