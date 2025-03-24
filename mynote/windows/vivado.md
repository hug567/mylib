# 1、常用操作：

- 打开图形设计窗口：

```bash
Flow -> Open Block Design -> design_1.bd
```

# 2、手动新建工程：

- 创建目录结构及文件：

```bash
├── init.tcl
└── src
    ├── constrs
    │   └── led.xdc
    └── sources
        └── led.v
```

- init.tcl：

```bash
set current_dir [pwd]
puts "current_dir: $current_dir"

create_project -force led ./ -part xc7z020clg400-2

add_files ./src/sources/led.v

add_files -fileset constrs_1 ./src/constrs/led.xdc
```

- led.v：

```bash
`timescale 1ns / 1ps

module led(
    input sys_clk,
    output reg led
    );
reg[31:0] timer_cnt;
always @(posedge sys_clk)
begin
    if (timer_cnt >= 32'd49_999_999)
    begin
        led <= ~led;
        timer_cnt <= 32'd0;
    end
    else
    begin
        led <= led;
        timer_cnt <= timer_cnt + 32'd1;
    end
end
endmodule
```

- led.xdc：

```bash
set_property PACKAGE_PIN U18 [get_ports sys_clk]
set_property IOSTANDARD LVCMOS33 [get_ports sys_clk]
set_property PACKAGE_PIN R19 [get_ports led]
set_property IOSTANDARD LVCMOS33 [get_ports led]

create_clock -period 20.000 -name sys_clk -waveform {0.000 10.000} [get_ports sys_clk]
```

- .gitignore：

```bash
# 项目生成的 cache 目录
*.cache/
*.hw/
*.ip_user_files/
*.runs/
*.sim/
*.gen/
*.tmp/
*.backup/
*.recovery/
*.xpr

# 生成的综合和实现结果
*.jou
*.log
*.str
*.wdb
*.dcp
*.xml
*.html
*.txt
*.ltx
*.bit
*.bin
*.bif
*.mcs
*.prm
*.rpt
*.tcl
*.pb
*.zip
*.tar.gz

# 仿真文件
*.wcfg
*.wdb
*.vcd
*.vstf
*.dat
*.mem
*.vvp
*.key

# ModelSim / QuestaSim 生成的文件
modelsim.ini
transcript
*.wlf
*.vstf
*.ucdb

# XSIM 仿真生成的文件
xsim.dir/
*.log
*.pb
*.wdb
*.mif

# Board Support Package (BSP) and SDK
.bsp/
.sdk/
.vitis/

# IP 核相关的文件
*.xcix
*.xci
*.xsa
*.bd
*.ds
*.bmm

# Xilinx IP 和生成文件
*.dcp
*.xdc
*.ngc
*.ncd
*.ngd
*.rpt
*.sysdef

# Constraint files
*.ncf
*.pcf

# Vivado HLS 生成的文件
*.log
*.dat
*.apcc

#-------------------------------------------------------------
# 一些特定的 IDE 文件
#-------------------------------------------------------------
# Quartus
db/
incremental_db/
.qws
.cmp

# ISE / PlanAhead
*.xise
*.ise
*.ngc
*.ngr
*.ncd
*.bit
*.bmm
*.rpt
*.html
*.xml

#-------------------------------------------------------------
# 一般 IDE/OS 相关的忽略文件
#-------------------------------------------------------------
# 临时文件
*.bak
*.sav
*.swp
*.tmp
*~

# macOS / Linux / Windows
.DS_Store
*.log
Thumbs.db
desktop.ini

#-------------------------------------------------------------
# 用户自定义 IP 和约束文件可以保留
#-------------------------------------------------------------
# 保留 HDL 和约束文件
!*.v
!*.sv
!*.vh
!*.vhd
!*.xdc
!*.tcl
!*.cfg
!*.m
```

- 打开vivado，在底部Tcl console中执行：

```bash
cd D:/code/vivado/led; source init.tcl
```

