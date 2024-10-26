# qemu运行freertos

## 1、arm：

```bash
# 安装编译器，ubuntu 18.04：
sudo apt install gcc-arm-none-eabi
# 下载源码，有较多submodule
git clone https://github.com/FreeRTOS/FreeRTOS.git --recurse-submodules --depth=1
# 进入demo目录：
cd FreeRTOS/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/build/gcc
# 编译：
make
# 运行：
qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel output/RTOSDemo.out -monitor none -nographic -serial stdio
```

