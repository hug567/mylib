# 1、编译dts：

```bash
# 安装：
sudo apt install device-tree-compiler

dtc -I dts -O dtb -o output.dtb input.dts
```

# 2、反编译dtb：

```bash
dtc -I dtb -O dts -o output.dts input.dtb
dtc -I dtb -O dts -o system.dts system.dtb
```

# 3、读取dts值：

```bash
# 读取二进制dts值
cat /sys/firmware/devicetree/base/serial\@3100000/reg | xxd
cat /proc/device-tree/amba/serial\@e0001000/reg | od -X
```

