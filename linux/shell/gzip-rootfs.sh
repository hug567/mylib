#!/bin/bash

# All path variables are absolute paths, and you can execute the current script anywhere.

MYLIB="${HOME}/code/mylib"
BUSYBOX="${HOME}/code/linux/busybox-1.27.2"
WORK_DIR="${HOME}/code/linux"
TEST_ELF="${MYLIB}/c/test-libc/obj/test-libc.elf"
LINUX_TEST="${MYLIB}/linux/linux-test/obj/linux-test.elf"

if [ -f "${WORK_DIR}/rootfs.img" ]; then
    echo "delete old file ${WORK_DIR}/rootfs.img"
    sudo rm -rf ${WORK_DIR}/rootfs.img
fi
if [ -f "${WORK_DIR}/rootfs.img.gz" ]; then
    echo "delete old file ${WORK_DIR}/rootfs.img.gz"
    sudo rm -rf ${WORK_DIR}/rootfs.img.gz
fi
if [ -d "${WORK_DIR}/rootfs" ]; then
    echo "delete old dir ${WORK_DIR}/rootfs/"
    sudo rm -rf ${WORK_DIR}/rootfs
fi

mkdir -p ${WORK_DIR}/rootfs
cd ${WORK_DIR}/rootfs

echo "copy busybox file to rootfs"
sudo cp -rf ${BUSYBOX}/_install/* ./
sudo mkdir -p proc sys dev etc etc/init.d tmp
sudo touch ./etc/init.d/rcS
sudo chmod a+x ./etc/init.d/rcS
sudo sh -c 'echo "#!/bin/sh\nmount -t proc none /proc\nmount -t sysfs none /sys\n/sbin/mdev -s" > ./etc/init.d/rcS'

echo "copy {LINUX_TEST} to rootfs"
sudo cp ${LINUX_TEST} ./
sudo chmod a+x ${LINUX_TEST}

echo "copy ${TEST_ELF} to rootfs"
sudo cp ${TEST_ELF} ./
sudo chmod a+x ${TEST_ELF}

echo "package rootfs.img"
find . | cpio -o --format=newc > ../rootfs.img

echo "gzip rootfs.img.gz"
cd ..
gzip -c rootfs.img > rootfs.img.gz

sudo rm -rf ${WORK_DIR}/rootfs.img
sudo rm -rf ${WORK_DIR}/rootfs
