# 1、自建rustdesk服务器：

## 1）、创建服务：

- ubuntu 22.04：

```bash
docker pull rustdesk/rustdesk-server

# hbbs - RustDesk ID注册服务器
# hbbr - RustDesk 中继服务器
cd /opt
sudo mkdir rustdesk
sudo chown -R hx:hx rustdesk
cd rustdesk
mkdir -p hbbs/root hbbr/root

# 运行docker镜像：
docker run \
    --name hbbs \
	-v /opt/rustdesk/hbbs/root:/root \
	-v /tmp/docker:/tmp/docker \
	-td \
	--net=host \
	rustdesk/rustdesk-server hbbs

docker run \
    --name hbbr \
	-v /opt/rustdesk/hbbr/root:/root \
	-v /tmp/docker:/tmp/docker \
	-td \
	--net=host \
	rustdesk/rustdesk-server hbbr

# 获取key：
echo $(cat /opt/rustdesk/hbbs/root/id_ed25519.pub)
```

- rustdesk使用到的网络端口：21114、21115、21116(tcp/udp)、21117、21118、21119

## 2）、开机自启动：

- 配合sytemd，开机时启动已创建好的docker容器；
