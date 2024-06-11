# 1、systemctl：

```bash
systemctl --help                           # 查看帮助
systemctl start xxx                        # 启动服务
systemctl researt xxx                      # 重启服务
systemctl stop xxx                         # 停止服务
systemctl -a                               # 查看所有unit
systemctl list-units                       # 列出单元
systemctl daemon-reload                    # 修改服务文件后重新加载
systemctl is-active xxx                    # 查看是否是开机自启
systemctl enable xxx                       # 使能开机自启
systemctl disable xxx                      # 关闭开机自启
systemctl list-timers                      # 列出所有定时任务
systemctl list-jobs                        # 列出活动任务
systemctl status xxx                       # 查看unit状态
systemctl list-dependencies xxx            # 列出服务依赖

# 重新加载service文件：
sudo systemctl daemon-reload
sudo systemctl restart test.service
sudo systemctl status test.service

# 重定向输出到文件
ExecStart=/bin/bash -c 'echo helloworld >> /tmp/systemd.log'

# ExecStart执行多条指令
ExecStart=/bin/bash -c '\
        date >> /tmp/systemd.log; \
        time=$(date); \
        num=$(date | head -c 2 | tail -c 1); \
        echo [$time] >> /tmp/systemd.log; \
        echo "num = $num" >> /tmp/systemd.log; \
        if [ $num == 2 ]; then \
                echo "num is 2" >> /tmp/systemd.log; \
        else \
                echo "num is not 2" >> /tmp/systemd.log; \
        fi \
        '
```

# 2、journalctl：

```bash
journalctl -u xxx                          # 查看service启动日志
journalctl -k                              # 查看kernel日志
# "emerg" (0), "alert" (1), "crit" (2), "err" (3), "warning" (4), "notice" (5), "info" (6), "debug" (7)
journalctl -k -p err                       # 查看err及以上级别日志
journalctl -k -f                           # 实时显示内核日志
```

# 3、systemd-analyze：

```bash
systemd-analyze blame                                  # 查看各服务启动时间
systemd-analyze plot > systemd_plot.svg                # 输出启动详情svg图像
systemd-analyze critical-chain                         # 显示默认启动时间单元时间关键链
systemd-analyze critical-chain xxx.service             # 显示指定单元时间关键链 (必须加.service后缀)
systemd-analyze dump > systemd_dump.log                # 输出全部单元状态日志
systemd-analyze log-level                              # 打印systemd日志级别
systemd-analyze log-target                             # 打印systemd日志输出目标
```

# 4、新增任务：

```bash
touch my_service.service
#----------------------------------------------#
[Unit]
Description=My Service
After=network.target

[Service]
ExecStart=/bin/bash /usr/sbin/myservice/main.sh
Restart=no

[Install]
WantedBy=multi-user.target
#----------------------------------------------#
sudo cp my_service.service /lib/systemd/system
sudo systemctl enable my_service
sudo systemctl start my_service
```

# 5、systemd-networkd：

```bash
# 有线网卡配置进来
```

