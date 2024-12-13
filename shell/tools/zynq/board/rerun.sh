#!/bin/bash
flag_file="/run/media/mmcblk0p3/not_load_cpu1"

if [ -f ${flag_file} ]; then
    echo "will rm ${flag_file}"
    rm ${flag_file}
    sync
fi

echo "system will reboot ..."
restart
