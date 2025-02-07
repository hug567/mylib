# 1、showdoc部署：

- 源码：https://github.com/star7th/showdoc
- 官网：https://www.showdoc.com.cn/
- 文档：https://www.showdoc.com.cn/3/65610

```bash
docker pull registry.cn-shenzhen.aliyuncs.com/star7th/showdoc
docker tag registry.cn-shenzhen.aliyuncs.com/star7th/showdoc:latest star7th/showdoc:latest

cd ~/temp
mkdir -p showdoc/html
docker run -d --name showdoc --restart=always --privileged=true -p 4999:80 -v /home/hx/temp/showdoc/html:/var/www/html/ star7th/showdoc
# 访问：
# 初始账号密码：showdoc/123456
http://10.110.0.3:4999
```

