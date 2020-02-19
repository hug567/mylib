#!/bin/bash

rm -rf rootfs.img rootfs.img.gz

cd rootfs

find . | cpio -o --format=newc > ../rootfs.img

cd ..

gzip -c rootfs.img > rootfs.img.gz
