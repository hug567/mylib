# 1、命令参数：

```bash
rsync     # 文件同步
    -r    # 递归处理子目录
    -l    # 保留软连接
    -H    # 保留硬连接
    -v    # verbose，显示详细信息
```

# 2、常用方式：

```bash
rsync -rlHv user@192.168.0.1:~/dir ./     # 同步远端目录到本地

# rsync指定端口
rsync -e 'ssh -p 1000' -rl name@192.168.0.1:~/dir ./
```

