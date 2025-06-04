# qemu运行freertos

## 1、arm：

-  下载工具链：
  - https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
    - https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz

- 编译：

```bash
# 安装编译器，ubuntu 18.04：
sudo apt install gcc-arm-none-eabi
# 下载源码，有较多submodule
git clone https://github.com/FreeRTOS/FreeRTOS.git --recurse-submodules --depth=1
# 进入demo目录：
cd FreeRTOS/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/build/gcc
# 配置gcc：
export PATH="$HOME/tools/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi/bin:$PATH"
# 验证gcc：
arm-none-eabi-gcc --version
# 编译：
make
# 运行：
qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel output/RTOSDemo.out -monitor none -nographic -serial stdio
```

