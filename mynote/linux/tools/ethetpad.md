# Etherpad本地部署

- 网站：https://etherpad.org/#

- github：https://github.com/ether/etherpad-lite

## 1、docker部署etherpad：

```bash
# 拉取失败可尝试使用代理拉取，详情见docker文档：
docker pull etherpad/etherpad
cd ~
mkdir ethertpad
chmod -R 777 ethertpad
docker run -d --name etherpad --restart always -p 9001:9001 -v /mnt/sdb:/mnt/sdb -v /home/hx/ethertpad:/opt/etherpad-lite/var etherpad/etherpad:latest
```



