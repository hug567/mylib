# 1、安装：

```bash
# Ubuntu 20.04, ubuntu 22.04
sudo apt install ripgrep

# Ubuntu 18.04
sudo add-apt-repository ppa:x4121/ripgrep
sudo apt update
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

rg "xxx" dir/                                # 在指定目录下搜索
  --no-ignore                                # 不忽略.gitignore忽略的文件
  -i                                         # 不区分大小写
  -v                                         # 显示不匹配的行
  -e                                         # 使用正则表达式
  -A <num>                                   # 显示匹配行后<num>行
  -B <num>                                   # 显示匹配行前<num>行
  -C <num>                                   # 显示匹配行前后各<num>行
  -c                                         # 只显示文件中匹配个数
  -l                                         # 只显示匹配的文件
  -g "*.c"                                   # 只在.c文件中查找
  -g "*.{c,h}"                               # 只在.c和.h文件中查找
  -g "\!*.c"                                 # 不在.c文件中查找
  -g "\!tools/*"                             # 不在tools目录中查找
  -z                                         # 搜索压缩文件
  -a                                         # 搜索二进制文件
  -j <num>                                   # 多线程搜索
  --type-list                                # 显示支持的文件类型
  -t <type>                                  # 在指定类型文件中搜索

# 查找指定文件，若find结果为空，将搜索所有文件
rg -e "text" $(find . -name kernel.log)

# 跨行搜索
rg -e "struct filename \*\ngetname\(const char" --multiline ./

# 排除单个目录
rg -e "CONFIG_CMD_PART" -g "\!configs"
```

