# 1、常用命令：

```bash
taskset -p <pid>                           # 查看指定进程邦核
taskset -p <mask> $$                       # 设置当前进程邦核，可在shell脚本中使用
taskset -c <cpu list> <cmd>                # 设置邦核执行命令
```
