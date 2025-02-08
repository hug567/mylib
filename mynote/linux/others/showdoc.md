# 1、showdoc部署：

- 源码：https://github.com/star7th/showdoc
- 官网：https://www.showdoc.com.cn/
- 文档：https://www.showdoc.com.cn/3/65610

```bash
# 下载docker镜像：
docker pull registry.cn-shenzhen.aliyuncs.com/star7th/showdoc
# 重命名docker镜像：
docker tag registry.cn-shenzhen.aliyuncs.com/star7th/showdoc:latest star7th/showdoc:latest
# 创建数据目录：
cd ~/temp
mkdir -p showdoc/html
# 运行docker镜像：
docker run -d --name showdoc --restart=always --privileged=true -p 4999:80 -v /home/hx/temp/showdoc/html:/var/www/html/ star7th/showdoc
# 访问：
# 初始账号密码：showdoc/123456
http://10.110.0.3:4999
```

