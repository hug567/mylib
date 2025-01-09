# 1、常见用法：

```bash
# 在当前下查找文件名中有test的文件
find . -name "*test*"

# 在当前目录下，排除build目录，查找文件名中有core-image-weston的文件
find . -path './build' -prune -o -name "*core-image-weston*"
# 正则表达式匹配排除的目录：
find . -path './build*' -prune -o -name "*core-image-weston*"

# 在当前目录下，排除build目录，排除.bb文件和.png文件，查看文件名中含有core-image的文件
find . \( -path './build' -o -path '*.bb' -o -path "*.png" \) -prune -o -name "*core-image*" -print

# 在当前目录下，排除build目录，查找文件名中有指定字符串的文件
find $(ls | grep -v build) -name "*openssl*"
```
