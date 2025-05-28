# 1、命令参数：

```bash
date
	--help
```

# 2、常见用法

## 2.1、读取时间：

```bash
date
date "+%Y-%m-%d %H:%M:%S"
# 读取unix时间戳：
date +%s
```

## 2.2、设置时间：

```bash
date -s "2023-09-09"
date -s "17:11:00"
date -s "2023-09-09 17:11:30"
date -s "@1715623412"
```

