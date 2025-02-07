# 1、Focalboard搭建：

- 源码：https://github.com/mattermost-community/focalboard

- 系统：Ububtu 22.04

```bash
sudo apt install sqlite3
# 下载软件包：
wget https://github.com/mattermost-community/focalboard/releases/download/v7.10.6/focalboard-server-linux-amd64.tar.gz
# 解压：
tar -xvf focalboard-server-linux-amd64.tar.gz
# 进入目录：
cd focalboard
# 创建目录：
mkdir files
# 创建数据库：
sqlite3 focalboard.db "create table t(f int); drop table t;"
# 创建配置文件：
vim config.json
#----------------------------------------------------#
{
    "serverRoot": "http://localhost:8000",
    "port": 8000,
    "dbtype": "sqlite3",
    "dbconfig": "./focalboard.db",
    "postgres_dbconfig": "dbname=focalboard sslmode=disable",
    "useSSL": false,
    "webpath": "./pack",
    "filespath": "./files",
    "telemetry": true,
    "prometheusaddress": ":9092",
    "session_expire_time": 2592000,
    "session_refresh_time": 18000,
    "localOnly": false,
    "enableLocalMode": true,
    "localModeSocketLocation": "/var/tmp/focalboard_local.socket"
}
#----------------------------------------------------#
# 启动：
./bin/focalboard-server
# 第一次进入需注册账号
```

