# 1、安装：

```bash
# 安装
sudo apt install ripgrep

```

# 2、常见用法：

```bash
# 使用正则表达式搜索
rg -e "xxx" ./
  -A <num>       # 打印匹配行之前的num行
  -B <num>       # 打印匹配行之后的num行
  -C <num>       # 打印匹配行之前和之后的num行
  --binary       # 搜索二进制文件
```

