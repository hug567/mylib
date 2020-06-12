#!/bin/bash

mylib="${HOME}/code/mylib"
test_libc_elf="${mylib}/c/test-libc/obj/test-libc.elf"
linux_test_elf="${mylib}/linux/linux-test/obj/linux-test.elf"
rootfs_dir="${HOME}/code/rootfs"

if [ -f "${rootfs_dir}/rootfs.img" ]; then
    echo "delete old ${rootfs_dir}/rootfs.img"
    sudo rm -rf ${rootfs_dir}/rootfs.img
fi

mkdir -p ${rootfs_dir}/rootfs
cd ${rootfs_dir}/rootfs

echo "copy busybox file to rootfs"
sudo cp -rf ../busybox-1.27.2/_install/* ./
sudo mkdir -p proc sys dev etc etc/init.d tmp usr usr/bin
sudo touch ./etc/init.d/rcS
sudo chmod a+x ./etc/init.d/rcS
sudo sh -c 'echo "#!/bin/sh\nmount -t proc none /proc\nmount \
-t sysfs none /sys\n/sbin/mdev -s" > ./etc/init.d/rcS'

echo "copy ${linux_test_elf} to rootfs"
sudo cp -r ${linux_test_elf} usr/bin
sudo chmod a+x ${linux_test_elf}

echo "copy ${test_libc_elf} to rootfs"
sudo cp ${test_libc_elf} usr/bin
sudo chmod a+x ${test_libc_elf}

echo "package rootfs.img"
find . | cpio -o --format=newc > ../rootfs.img

echo "gzip rootfs.img.gz"
cd ..
gzip -c rootfs.img > rootfs.img.gz

sudo rm -rf rootfs.img
sudo rm -rf rootfs
