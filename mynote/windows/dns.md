# 1、windows设置本地域名解析：

```bash
C:\Windows\System32\drivers\etc\hosts
#---------------------------------------------------------#
10.110.0.3 gitlab.rhosoon.com
#---------------------------------------------------------#

# 配置科学上网工具的路由：
# 1、v2rayN:
设置 -> 路由设置 -> 直连的Domain或IP -> Domain: gitlab.rhosoon.com(注意在上一行末尾添加逗号) -> IP: 10.110.0.3(注意在上一行末尾添加逗号)
#---------------------------------------------------------#
Domain                                      IP
geosite:cn,                                 geoip:private,
domain:vvvdj.com,                           geoip:cn,
gitlab.rhosoon.com                          10.110.0.3
#---------------------------------------------------------#

# 浏览器访问
http://gitlab.rhosoon.com:9002
https://gitlab.rhosoon.com:9003
```

