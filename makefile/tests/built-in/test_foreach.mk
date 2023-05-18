# use foreach to traverse every member
# run: make -f file.mk
# 2023.05.18

names := file01 file02 file03
$(info [names:] $(names))
files := $(foreach f,$(names),$(f).o)
$(info [files]: $(files))

all:
	@#
