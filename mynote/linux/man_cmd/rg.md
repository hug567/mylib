# 1、安装：

```bash
# Ubuntu 20.04
sudo apt install ripgrep

# Ubuntu 18.04
sudo add-apt-repository ppa:x4121/ripgrep
sudo apt update
sduo apt install ripgrep
```

# 2、常见用法：

```bash
# 使用正则表达式搜索
rg -e "xxx" ./
  -A <num>       # 打印匹配行之前的num行
  -B <num>       # 打印匹配行之后的num行
  -C <num>       # 打印匹配行之前和之后的num行
  --binary       # 搜索二进制文件

# 查找指定文件，若find结果为空，将搜索所有文件
rg -e "text" $(find . -name kernel.log)
```

