# 1、使用hdf文件创建petalinux工程：

```bash
# petalinux 2019.1
# 先准备好hdf文件：
mkdir hdf_dir
mv system.hdf hdf_dir
# 进入bash，不能在zsh中编译
bash
source /opt/pkg/petalinux/settings.sh
petalinux-create --type project --template zynq --name ax_peta
cd ax_peta/
petalinux-config --get-hw-description ../hdf_dir
petalinux-config -c kernel
petalinux-config -c rootfs
petalinux-build
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force
# 不打包fpga程序
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --u-boot --force
```

