# learning makefile build-in function: filter-out
# run: make -f file.mk
# 2023.05.18

all = file01.c file02.c header.h file03.c
$(info [all:] $(all))
ret = $(filter-out %.h,$(all))
$(info [filter-out %.h]: $(ret))

all:
	@#
