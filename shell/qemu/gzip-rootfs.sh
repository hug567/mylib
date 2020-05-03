#!/bin/bash

# All path variables are absolute paths, and you can execute the current script anywhere.

MYLIB="${HOME}/code/mylib"
LINUX_TEST="${MYLIB}/linux/linux-test/linux-test.elf"
BUSYBOX="${HOME}/code/linux/busybox-1.27.2"
WORK_DIR="${HOME}/code/linux"

if [ -f "${WORK_DIR}/rootfs.img" ]; then
    sudo rm -rf ${WORK_DIR}/rootfs.img
fi
if [ -f "${WORK_DIR}/rootfs.img.gz" ]; then
    sudo rm -rf ${WORK_DIR}/rootfs.img.gz
fi
if [ -d "${WORK_DIR}/rootfs" ]; then
    sudo rm -rf ${WORK_DIR}/rootfs
fi

mkdir -p ${WORK_DIR}/rootfs
cd ${WORK_DIR}/rootfs
sudo cp -rf ${BUSYBOX}/_install/* ./
sudo mkdir proc sys dev etc etc/init.d
sudo touch ./etc/init.d/rcS
sudo chmod a+x ./etc/init.d/rcS
sudo sh -c 'echo "#!/bin/sh\nmount -t proc none /proc\nmount -t sysfs none /sys\n/sbin/mdev -s" > ./etc/init.d/rcS'

sudo cp ${LINUX_TEST} ./
sudo chmod a+x ${LINUX_TEST}

find . | cpio -o --format=newc > ../rootfs.img
cd ..
gzip -c rootfs.img > rootfs.img.gz
