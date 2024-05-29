# 1、添加定时任务：

```bash
crontab -e    # 编辑工作表
crontab -l    # 列出工作表中的任务
crontab -r    # 删除所有定时任务

# crontab命令：每一行是一条定时任务
分 时 日 月 周 命令

*    # 取值范围内的所有值
/    # 没隔一定时间
-    # 从a到b
,    # 散列数字

# 例：
0 * * * * echo "$(date) > /tmp/crontab.log"     # 每小时的第0分钟执行echo命令
```