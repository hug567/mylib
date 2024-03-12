# 1、常见用法：

```bash
# 启动xsct: vivado 2017.4
/opt/Xilinx/SDK/2017.4/bin/xsct

# 查看帮助
help
# 查看指定命令帮助
help connect

# 通过jtag启动u-boot
# 连接：
connect -url tcp:127.0.0.1:3121
# 查看硬件：
targets
```

## 1）、linux中通过JTAG运行u-boot：

```bash
# 测试硬件：zynq7020 arm
# 调整插针设置成从JTAG启动，连接JTAG线，并按一下reset键：

# 运行xsct并连接芯片：
/opt/Xilinx/SDK/2017.4/bin/xsct
connect -url tcp:127.0.0.1:3121
targets

# 下载fsbl并运行：
targets -set -nocase -filter {name =~ "arm*#0"}          # 或：target 2
dow "/home/hx/jtag-zynq/zynq_fsbl.elf"
con; after 5000; stop

# 运行初始化脚本：
targets 1
source /home/hx/temp/flash-zynq/ps7_init.tcl
ps7_init

# 下载dtb：
targets -set -nocase -filter {name =~ "arm*#0"}
set deviceTreeOffset 0x100000
dow -data "/home/hx/temp/flash-zynq/system.dtb" 0x100000

# 下载u-boot：
targets -set -nocase -filter {name =~ "arm*#0"}
dow "/home/hx/temp/flash-zynq/u-boot.elf"

# 下载linux镜像到内存
dow -data "/home/hx/temp/flash-zynq/image-nothing.ub" 0x10000000

# 运行u-boot：
con

# 去串口查看是否运行了u-boot，若u-boot成功启动，在u-boot中启动linux镜像：
bootm 0x10000000

# 退出
exit
```



