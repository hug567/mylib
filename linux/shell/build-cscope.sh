#!/bin/bash

find ./ \
    ! -path "./build-*" \
    ! -type l \
    -name "*.c" \
  -o \
    ! -path "./build-*" \
    ! -type l \
    -name "*.h" \
  > cscope.file

cscope -Rbq -i cscope.file

rm -rf cscope.file
