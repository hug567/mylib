# run shell cmd in makefie
# run: make -f file.mk
# 2023.04.27

ret = $(shell echo "" > /tmp/makefile.log)
ret2 = $(shell echo "hello makefile" >> /tmp/makefile.log)

CUR_DIR = $(shell cd .; pwd)

all:
	@echo "[hx-debug] CUR_DIR = ${CUR_DIR}"

temp:
	@echo "[hx-debug] ret = ${ret}"
	@echo "[hx-debug] ret2 = ${ret2}"
