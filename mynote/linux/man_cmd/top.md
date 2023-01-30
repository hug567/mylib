# 1、基本用法

```bash
top                                       # 连续查看进程状态
top -n 1                                  # 查看一次
top -u <user>                             # 查看指定用户进程
top -p <pid>                              # 查看指定pid进程
top -H                                    # 查看线程
top -H -p <pid>                           # 查看指定进程所有线程
top -> k -> <pid>                         # 向指定进程发送SIGTERM信号(kill)
top -> r -> <pid> -> <nice>               # 修改指定进程的nice值
top -b -n 1 > top.log                     # 所有进程信息存入文件中
top -H -b -n 1 > top.log                  # 所有线程信息存入文件中

# 交互式命令：
  c                                       # 切换显示命令名称与完整命令行
  m                                       # 不同样式显示内存使用信息
  t                                       # 不同样式显示cpu使用信息
  P                                       # 按cpu使用降序排列
  M                                       # 按内存使用降序排列
  w                                       # 将当前配置写入~/.toprc
```

# 2、结果含义

```bash
 $ top -n 1
# 22:02:43 ：系统当前时间
# up 42 days ：系统启动时间
# 53 users：当前登录用户数
# load average: 0.29, 0.18, 0.18 ：距离现在1分钟、5分钟、15分钟的负载情况
top - 22:02:43 up 42 days,  8:00, 53 users,  load average: 0.29, 0.18, 0.18
# 任务数： 总任务        运行中        休眠           停止        僵尸进程
Tasks: 511 total,   2 running, 479 sleeping,   0 stopped,  30 zombie
# us：用户空间cpu占用百分比
# sy：内核空间cpu占用百分比
# ni：改变过优先级的进程cpu占用百分比
# id：空闲cpu百分比
# wa：IO等待cpu占用百分比
# hi：硬件中断cpu占用百分比
# si：软中断CPU占用百分比
# st：hypervisor占用cpu百分比
%Cpu(s):  1.4 us,  2.8 sy,  0.0 ni, 95.8 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
#            总内存(MB)       空闲内存(MB)   已使用内存(MB)       缓存(MB)
MiB Mem :  31770.4 total,   2446.4 free,  10415.0 used,  18909.0 buff/cache
#           交换区总大小(MB)      空闲(MB)      已使用(MB) 
MiB Swap:   2048.0 total,      0.1 free,   2047.9 used.  20780.8 avail Mem
# PR: 实时优先级，OS动态调整，用户不能修改，值越小优先级越高
#   值为rt或大于0的数，
# NI: nice值，-20~19，值越小，优先级越高
# VIRT：虚存占用(kb)
# RES：物存占用(kb)
# SHR：共享内存占用(kb)
# S：进程状态，R(运行)、S(睡眠)、D(不可中断睡眠)、T(跟踪/停止)、Z(僵尸)
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
    932 root      20   0 1078932   8188   3140 S   6.2   0.0  31:03.71 NetworkManager
```
