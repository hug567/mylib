# 搭建MrDoc觅思文档

# 1、docker搭建MrDoc：

```bash
cd /opt
mkdir -p MrDoc/config 
mkdir -p MrDoc/config MrDoc/media
docker pull jonnyan404/mrdoc-alpine

docker run \
    -d --name mrdoc \
    -p 10086:10086 \
    -p 9000:9000 \
    --restart=always \
    -v /mnt/sdb:/mnt/sdb \
    -v /opt/MrDoc/config:/app/MrDoc/config \
    -v /opt/MrDoc/media:/app/MrDoc/media \
    -v /tmp/docker:/tmp/docker \
    -v /var/run/docker.sock:/var/run/docker.sock \
    jonnyan404/mrdoc-alpine:latest
```

