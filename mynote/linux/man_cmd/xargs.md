# 1、常见用方式：

```bash
find . -name "file.txt" | xargs md5sum
find . -name "file.txt" | xargs file
find . -name "file.txt" | xargs du -sh
find . -name "file.txt" | xargs ls -l

# -t: 先打印命令再执行
find . -name "file.txt" | xargs -t md5sum
```

