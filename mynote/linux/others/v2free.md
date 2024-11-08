# 1、基本信息：

- v2free机场：https://cdn.v2free.top/

- 账号：huangxing567@163.com

# 2、linux中使用：

## 1）、命令行中使用：

```bash
# 创建配置文件目录：
mkdir -p ~/.config/mihomo/
cd  ~/.config/mihomo/
# 下载clash命令：
curl https://cdn.v2free.top/ssr-download/clash-linux.tar.gz -o clash-linux.tar.gz
tar -xvf clash-linux.tar.gz
chmod +x clash-linux
# 下载配置文件，重新加下载即可更新订阅节点：
wget -U "Mozilla/6.0" -O ~/.config/mihomo/config.yaml "https://cdn.v2free.top/link/gi0NXWB4bw9Sfpui?clash=2"
# 启动clash：
./clash-linux

# 打开新窗口，设置代理：
export http_proxy="http://127.0.0.1:7890"; export https_proxy="http://127.0.0.1:7890"
# 测试
wget google.com
```

## 2）、配置网页管理：

```bash
# 下载clash-dashboard，选择一个目录放置，如：/home/hx/tools/clash/clash-dashboard

# 在config.yaml中添加：
#-----------------------------------------------------------------#
external-controller: 10.110.0.3:9090 # 本机访问，建议使用 127.0.0.1:9090/ui, 10.110.0.3:9090/ui
external-ui: /home/hx/tools/clash/clash-dashboard # clash-dashboard的路径
secret: 'hx2023clash' # 连接的密钥，自行设置
#-----------------------------------------------------------------#
```

