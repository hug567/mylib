# 1、命令参数：

```bash
sudo apt install stress

stress
	-v            # verbose
	-t N          # 超时时间N秒
	-c N          # 创建N个线程调用sqrt()
	-i N          # 创建N个线程调用sync()
	-m N          # 创建N个线程调用malloc()/free()
		--vm-bytes B    # 每次malloc字节数，默认值256MB
	-d N          # 创建N个线程调用write()/unlink()
		--hdd-bytes B    # 每次写入字节数，默认值1G
```

# 2、常见用法：

```bash
stress -d 2 --hdd-bytes 3G
```

