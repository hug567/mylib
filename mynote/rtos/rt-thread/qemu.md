# qemu运行rt-thread：

## 1、qemu arm：

- ubuntu 22.04：

```bash
# 安装工具：
sudo apt-get install scons libncurses5-dev
pip install kconfiglib
# 下载代码：
git clone https://github.com/RT-Thread/rt-thread.git
# 下载编译器：
wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
# 解压：
tar -xvf arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
# 验证编译器：
/home/hx/tools/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc --version
# 设置编译器路径：
export RTT_EXEC_PATH=/home/hx/tools/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi/bin
# 进入示例目录：
cd bsp/qemu-vexpress-a9
# 手动配置：
scons --menuconfig
# 加载环境变量：
source ~/.env/env.sh
# 更新包：
pkgs --update
# 编译：
scons
# 运行：
./qemu.sh
```

