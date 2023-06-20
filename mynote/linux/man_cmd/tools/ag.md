# 1、安装：

```bash
sudo apt install silversearcher-ag
```

# 2、参数含义：

```bash
-A <num>                      # 打印匹配行之后的num行
-B <num>                      # 打印匹配行之前的num行
-u                            # 搜索所有文件
```

# 3、常用命令：

```bash
ag "string" --ignore-dir <dir>                 # 排除目录
ag -i "string"                                 # 大小写不敏感
ag -w "string"                                 # 全词匹配(大小写敏感)

# 正则表达式
[^ABC]                                         # 匹配出来[...]里的字符
```
