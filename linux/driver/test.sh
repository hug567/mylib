#!/bin/sh

cd /lib/modules

DRIVER_KO=myuart.ko
if [ -f $DRIVER_KO ]; then
    insmod $DRIVER_KO
fi
