#!/bin/bash

# ubuntu 20.04
# sudo apt install gcc-mips-linux-gnu
# sudo apt install gcc-mipsel-linux-gnu

#mips-linux-gnu-gcc -mfp32 -march=R2000 hello.c
#mips-linux-gnu-gcc -mfp32 -march=interaptiv -LB hello.c
#mips-linux-gnu-gcc -mips32r2 -march=interaptiv hello.c
mipsel-linux-gnu-gcc -static -mips32r2 -march=interaptiv hello.c
