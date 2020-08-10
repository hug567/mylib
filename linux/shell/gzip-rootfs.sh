#!/bin/bash

base_dir="${HOME}/code/linux"
busybox_dir="${base_dir}/busybox-1.27.2"
rootfs_dir="${base_dir}/rootfs"

mylib="${HOME}/code/mylib"
test_libc_elf="${mylib}/c/test-libc/obj/test-libc.elf"
linux_test_elf="${mylib}/linux/linux-test/obj/linux-test.elf"

cd ${base_dir}
mkdir -p rootfs
cd rootfs

echo "[INFO]: copy busybox file to rootfs"
sudo cp -rf ${busybox_dir}/_install/* ./
sudo mkdir -p proc sys dev etc etc/init.d tmp usr usr/bin lib/modules
sudo touch ./etc/init.d/rcS
sudo chmod a+x ./etc/init.d/rcS
sudo sh -c 'echo "#!/bin/sh\nmount -t proc none /proc\nmount \
-t sysfs none /sys\n/sbin/mdev -s" > ./etc/init.d/rcS'

echo "[INFO]: copy ${linux_test_elf} to rootfs"
sudo cp -r ${linux_test_elf} usr/bin
sudo chmod a+x ${linux_test_elf}

echo "[INFO]: copy ${test_libc_elf} to rootfs"
sudo cp ${test_libc_elf} usr/bin
sudo chmod a+x ${test_libc_elf}

echo "[INFO]: package rootfs.img"
find . | cpio -o --format=newc > ../rootfs.img

echo "[INFO]: gzip rootfs.img.gz"
cd ..
gzip -c rootfs.img > rootfs.img.gz

sudo rm -rf rootfs.img
sudo rm -rf rootfs
