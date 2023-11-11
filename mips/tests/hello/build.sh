#!/bin/bash

# ubuntu 20.04
# sudo apt install gcc-mips-linux-gnu

mips-linux-gnu-gcc -mfp32 -march=R2000 hello.c
