# 1、进程信息：

```bash
# 查看所有进程
Get-Process

# 进程按cpu占用降序排列
Get-Process | Sort-Object CPU -Descending
# 查看cpu占用最高的20个进程
Get-Process | Sort-Object CPU -Descending | Select-Object -First 20

# 查看内存占用最高的20个进程
Get-Process | Sort-Object WS -Descending | Select-Object -First 20
```

