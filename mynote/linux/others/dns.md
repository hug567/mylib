# DNS服务器搭建

## 1、搭建dns服务器：

```bash
sudo apt install bind9 bind9utils bind9-doc
cd /etv/bind
sudo vim named.conf.local



# bind9.service控制
sudo systemctl start bind9.service
sudo systemctl stop bind9.service
sudo systemctl restart bind9.service
sudo systemctl reload bind9.service
sudo systemctl status bind9.service
```

