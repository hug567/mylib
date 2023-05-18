# learn to print logs using the makefile function
# run: make -f file.mk
# 2023.05.18

$(info this is an info log)
# warning: will print current file and line number
$(warning this is an warning log)
# error: will print current file and line number, make will stop
$(error this is an error log)

all:
	@#
