# 1、编译：

```bash
# 源码位置：tools/testing/selftests
cd build-aarch64
mkdir -p tools/testing/selftests
make -C ../tools/testing/selftests O=`pwd`/tools/testing/selftests ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j
```

