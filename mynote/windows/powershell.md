# 1、常用命令：

```bash
echo $pshome                     # 查看powershell home目录
echo $profile                    # 查看powershell配置文件
test-path $profile               # 测试配置文件是否存在

# Windows创建软连接:
mklink /j leetcode_0026.c G:\MyProgram\Git\mylib\c\leetcode\leetcode_0026.c
```

# 2、进程信息：

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

# 3、查看文件md5值：

```bash
# 需在powershell中执行：
Get-FileHash <file> -Algorithm MD5 | FOrmat-List
```

