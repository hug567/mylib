# 1、常见用法：

```bash
# 使用代理
wget -e "http_proxy=http://proxy.xxx.com:8080" -e "https_proxy=https://proxy.xxx.com:8080" http://file.tar.xz

# 设置用户名和密码
wget --http-user=username --http-passwd=passwd http://file.tar.xz
```

