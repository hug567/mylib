# 1、漏洞平台：

- CVE：https://cve.mitre.org/
- linux CVE：https://cve.mitre.org/cgi-bin/cvekey.cgi?keyword=linux

# 2、数组访问越界：

## 1）、访问数组上界错误：

```c
for (i = 0; i <= size; i++)        //应该是i < size
```

# 3、字符串访问越界：

