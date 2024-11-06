# 1、license申请：

- visual license过期，可登录visual svn网站，随便填写一个名称和邮箱，申请一个45天的临时license；
- 申请网址：https://www.visualsvn.com/server/licensing/evaluation/

- license在注册表中的存储位置：

```bash
# 注册表项位置：
HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\VisualSVN\VisualSVN Server
# license条目：
"License"="ERvvVOHWA3AgkMzhlOTY1NzEtMzFiYS00MGE5LTgwNjctNzUxNmRmY2E4YzBk"
```

- 未验证的思路：安装一个全新的操作系统，安装visual svn server，将License复制到原机器上，验证license是否延长了？