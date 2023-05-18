# strip spaces and tab at the beginning and ending of a string
# run: make -f test_strip.mk
# 2023.05.18

str = 123   456  	      	789       
$(info [str:] [$(str)])
ret = $(strip $(str))
$(info [strip]: [$(ret)])

all:
	@#
