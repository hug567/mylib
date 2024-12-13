#!/bin/bash

sleep 5
val=1
for i in $(seq 1 10); do
    val_16=$(printf 0x%08x $val)

    echo "will run cmd: poke 0x43cc0000 $val_16"
    poke 0x43cc0000 $val_16
    sleep 1

    val=$(($val << 1))
    let val=val+1
done
