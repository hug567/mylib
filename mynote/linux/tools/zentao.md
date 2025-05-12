# 禅道开源版：

## 1、安装：

- 官网：https://www.zentao.net/
- linux一键安装：https://www.zentao.net/book/zentaopms/458.html

```bash
# ubuntu 22.04 server安装：
cd /opt
sudo wget https://www.zentao.net/dl/zentao/18.5/ZenTaoPMS.18.5.zbox_64.tar.gz
sudo tar -xvf ZenTaoPMS.18.5.zbox_64.tar.gz

# 启动：
sudo /opt/zbox/zbox --aport 8080 --mport 3307 start
# 网页访问，默认账户密码：admin / 123456
http://192.168.99.93:8080/
```

