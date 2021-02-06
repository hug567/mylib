#!/bin/sh

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
