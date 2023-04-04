# 1、简介：

- 功能：跟踪进程创建，为每次进程创建打印一条信息，通过跟踪execve系统调用来实现；

# 2、安装：

```bash
git clone https://github.com/brendangregg/perf-tools

# 确认kernel是否开始CONFIG_KPROBES
cat /proc/config.gz | gunzip | grep KPROBES
# ubuntu
cat /boot/config-$(uname -r) | grep KPROBES
```

# 3、使用：

