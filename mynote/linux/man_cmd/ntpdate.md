# 1、设置时区：

```bash
# 查看时区：
#   CST：中国标准时间
#   UTC：世界标准时间，UTC=CST-8
#   GMT：格林尼治标准时间
date
timedatectl status

# 修改时区：
sudo dpkg-reconfigure tzdata        # 改为: "Asia/Shanghai"
# 或:
timedatectl set-timezone "Asia/Shanghai"
```

# 2、同步时间：

```bash
# 时间校准：
sudo apt install ntpdate

sudo ntpdate -u cn.pool.ntp.org              # 中国开源免费NTP服务器
sudo ntpdate -u cn.ntp.org.cn
sudo ntpdate -u ntp.aliyun.com               # 开源免费NTP服务器

# 设置为24小时制
sudo vim /etc/default/locale
# 末尾添加以下一行，然后重启
LC_TIME=en_DK.UTF-8
```
