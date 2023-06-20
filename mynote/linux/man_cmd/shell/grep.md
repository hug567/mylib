# 1、参数含义：

```bash
grep
  -n                                     # 显示行号
  -r                                     # 递归查找子目录
  -a                                     # 搜索二进制文件
  -v                                     # 反向匹配，不包含指定字符串
  -A <num>                               # 显示匹配行之后的num行
  -B <num>                               # 显示匹配行之前的num行
  -E                                     # 匹配扩展正则表达式
  -G                                     # 匹配基础正则表达式
  -P                                     # 匹配Perl正则表达式
  -h                                     # 不显示文件名
```

# 2、常见用法：

```bash
grep -nr "text" ./                                           # 递归搜索子目录，结果显示行号
grep -anr "text" ./                                          # 同时搜索二进制文件
pa aux | grep "sshd" | grep -v " grep "                      # 反向过滤
ps aux | grep -E "sshd|httpd"                                # 逻辑或，匹配字符串之一

# 查找指定文件中的字符，注意不加-r
grep -n "text" $(fine . -name "kernel.log")
```
