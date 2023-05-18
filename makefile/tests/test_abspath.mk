# get abs path in makefile
# run: make -f file.mk
# 2023.04.27

CUR_DIR = $(shell cd .; pwd)

all:
	@echo "[hx-debug] CUR_DIR = ${CUR_DIR}"
