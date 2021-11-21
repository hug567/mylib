################################################################################
# python练习：文件
# python版本：python 3.6.9
# 时间：2021-11-21
################################################################################
import os
import sys

file_name = 'rfile.txt'

# 读取文件
with open(file_name) as file_obj:
    contents = file_obj.read()
    print(contents)

# 读取文件
fobj = open(file_name)
cts = fobj.read()
print(cts)

# 逐行读取
with open(file_name) as file_obj:
    for line in file_obj:
        print(line, end='')

# 读取文件至以行为元素的列表
with open(file_name) as file_obj:
    lines = file_obj.readlines()
    print(lines)
    # 遍历列表
    for line in lines:
        print(line.rstrip())

wfname = 'wfile.out'

# 写入文件
with open(wfname, 'w') as file_obj:
    file_obj.write("practice python write to file\n")
    file_obj.write("write second line\n")
with open(wfname) as file_obj:
    print(file_obj.read(), end='', sep='')

# 附加到文件
with open(wfname, 'a') as file_obj:
    file_obj.write("append third line to file\n")
with open(wfname) as file_obj:
    print(file_obj.read(), end='', sep='')

# 删除文件
os.remove(wfname)
