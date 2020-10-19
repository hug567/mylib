# git获取指定文件的最早与最新一次提交时间

import os
import subprocess

path = "./main.c"
time_out = 10

# 最早提交时间
cmd = "git log --pretty=format:'%cd' --date=format:'%Y-%m-%d %H:%M:%S' " + path + " | tail -1"
sub = subprocess.Popen(cmd, stdin=subprocess.PIPE, stderr=subprocess.PIPE,
    stdout=subprocess.PIPE, universal_newlines=True, shell=True, bufsize=1)
sub.wait(time_out)
early_time_str = sub.stdout.readline().strip("\n")
print(early_time_str)

# 最新提交年份
cmd = "git log --pretty=format:'%cd' --date=format:'%Y' -1 " + path
sub = subprocess.Popen(cmd, stdin=subprocess.PIPE, stderr=subprocess.PIPE,
    stdout=subprocess.PIPE, universal_newlines=True, shell=True, bufsize=1)
sub.wait(time_out)
latest_year_str = sub.stdout.readline().strip("\n")
print(latest_year_str)
