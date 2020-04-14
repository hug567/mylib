#!/bin/bash

line=$(sed -n '/xxx_test.so/=' test.txt)
line=(${line// / })
line=${line[1]}
sed -i "${line}"'s/xxx_test.so \\/xxx_test.so/g' test.txt
