#!/bin/bash

cd ~/code/mylib/linux/driver

NEED_DELETE=(
    ".tmp_versions"
    "Module.symvers"
    "modules.order"
    "*.mod.c"
    "*.ko"
    "*.o"
    ".*.cmd"
    ".*.mk"
    "vexpress/*.mod.c"
    "vexpress/*.ko"
    "vexpress/*.o"
    "vexpress/.*.cmd"
    "vexpress/.*.mk"
)

for file in ${NEED_DELETE[@]}
do
    echo "will delete: $file"
    rm -rf "$file"
done



exit

cd /lib/modules

DRIVER_KO=myuart.ko
if [ -f $DRIVER_KO ]; then
    insmod $DRIVER_KO
fi

cd /tmp
TEST_FILE=test_myuart
if [ -f ${TEST_FILE} ]; then
    ./${TEST_FILE}
fi
