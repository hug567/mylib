# pattern string substitution 
# run: make -f file.mk
# 2023.05.18

all = file01.c file02.c file03.c
$(info [all:] $(all))
ret = $(patsubst %.c,%.o,$(all))
$(info [patsubst]: $(ret))

all:
	@#
