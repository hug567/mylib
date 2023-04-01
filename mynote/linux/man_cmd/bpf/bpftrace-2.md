# 1、安装：

```bash
sudo apt install bpftrace
```

# 2、命令参数：

```bash
bpftrace
	-e 'program'        # 执行程序
	-o file             # 输出到文件
	-l                  # 打印追踪点
	-p PID
	-c "CMD"
	-v                  # verbose输出
```

- bpftrace支持的探测点有：
  - kprobe——内核函数的开始处 
  - kretprobe——内核函数的返回处 
  - tracepoint——内核静态追踪点 
  - profile——基于时间的采样 
  - interval——基于时间的输出 
  - software——内核软件事件 
  - hardware——处理器级事件
  - uprobe——用户级函数的开始处 
  - uretprobe——用户级函数的返回处 
  - usdt——用户级静态追踪点 

# 3、常见用法：

```bash
bpftrace -e 'BEGIN { printf("hello world\n"); }'

# 查看系统调用execve调用情况
bpftrace -e 't:syscalls:sys_enter_execve { printf("%s called %s\n", comm, str(args->filename)); }'

# 查看追踪点可用字段
bpftrace -lv "t:syscalls:sys_enter_execve"

# 查看用户程序可用追踪点
bpftrace -l "uprobe:/bin/bash"
# 追踪用户程序
bpftrace -e 'uretprobe:/bin/bash:readline { printf("readline: \"%s\"\n", str(retval)); }'

# 使用bpftrace脚本
bpftrace file.bt
```

## 1）、内建指令：

```bash
args        # 接口参数

pid                                      # 进程ID
tid                                      # 线程ID
cgroup                                   # 当前进程Cgroup ID
uid                                      # 用户ID
gid                                      # 组ID
nsecs                                    # 纳秒时间戳
cpu                                      # cpu号
comm                                     # 进程名称
kstack                                   # 内核栈追踪
ustack                                   # 用户栈追踪
arg0, arg1, ... etc.                     # Arguments to the function being traced
retval                                   # Return value from function being traced
func                                     # Name of the function currently being traced
probe                                    # 探测点全称
rand                                     # Random number of type u32.
curtask                                  # Current task_struct as a u64.
```

## 2）、内建函数：

```bash
hist(int n)
       Produce a log2 histogram of values of n
lhist(int n, int min, int max, int step)
       Produce a linear histogram of values of n
count()
       Count the number of times this function is called
sum(int n)
       Sum this value
min(int n)
       Record the minimum value seen
max(int n)
       Record the maximum value seen
avg(int n)
       Average this value
stats(int n)
       Return the count, average, and total for this value
delete(@x)
       Delete the map element passed in as an argument
str(char *s)
       Returns the string pointed to by s
printf(char *fmt, ...)
       Print formatted to stdout
print(@x[, int top [, int div]])
       Print a map, with optional top entry count and divisor
clear(@x)
       Delete all key/values from a map
sym(void *p)
       Resolve kernel address
usym(void *p)
       Resolve user space address
kaddr(char *name)
       Resolve kernel symbol name
uaddr(char *name)
       Resolve user space symbol name
reg(char *name)
       Returns the value stored in the named register
join(char *arr[])
       Prints the string array
time(char *fmt)                               # 打印当前时间
cat(char *filename)
       Print file content
ntop([int af, ]int|char[4|16] addr)
       Convert IP address data to text
system(char *fmt) (unsafe)                    # 执行shell命令
exit()                                        # 退出bpftrace
kstack([StackMode mode, ][int level])
       Kernel stack trace
ustack([StackMode mode, ][int level])
       User stack trace
```