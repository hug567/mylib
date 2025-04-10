# 1、常用命令：

```bash
iconv
	-l                       # 列出所有支持的编码
	-f <code>                # 原编码，如：utf-8、gbk、gb2312、ascii...
	-t <code>                # 目标编码
	-o <file>                # 输出为指定文件
```

# 2、常见用法：

```bash
# 将gb2312编码格式的文件转为utf-8编码
iconv -f gb2312 -t utf-8 main.c -o main-utf8.c
```

