# 1、在Windows中安装python：

```c
https://www.python.org/downloads/windows/                //python下载地址
/* 安装成功后再cmd中验证： */
python --version      //查看python版本
```

# 2、安装openpyxl：

```c
https://pypi.org/project/jdcal/#files                    //jdcal下载地址
/* 解压进入jdcal后执行： */
python setup.py install                                  //安装jdcal库

https://pypi.org/project/et_xmlfile/#files               //et_xmlfile下载地址
/* 解压进入et_xmlfile后执行： */
python setup.py install                                  //安装et_xmlfile库

https://pypi.org/project/openpyxl/#files                 //openpyxl下载地址
/* 解压进入openpyxl后执行： */
python setup.py install                                  //安装openpyxl库
```

# 3、Linux选择python版本：

```shell
# 查看python软连接指向文件：
ls -l /usr/bin/python /usr/bin/python2 /usr/bin/python3
# 添加链接管理：
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2 1 # 优先级为1
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 2 # 优先级为2
# 查看管理的python链接：
sudo update-alternatives --display python
# 选择python版本：
sudo update-alternatives --config python
```

# 4、pip/pip3：

```shell
# 查询包：https://pypi.org/

# 升级pip
python -m pip install --upgrade pip

# 查看已安装的python包
pip/pip3 list

# 安装python包
sudo pip/pip3 install xxx
# 安装指定版本
sudo pip3 install conan==1.60.1

# 卸载包
sudo pip3 unstall conan
# 卸载是指定版本
sudo pip3 unstall conan==2.0.4
# 卸载当前用户目录下的包
pip3 unstall conan
```

## 1)、离线安装pip包：
```bash
# 先在可联网的机器中下载pip包 (或从网址下载：https://pypi.org/)
pip3 download scapy
# 将下载的包上传到内网机器
scp scapy-2.5.0.tar.gz hx@192.168.0.100:~
# 进入内网机器包所在目录安装
pip3 install --no-index --find-links=./ scapy
# 查看已安装的pip包
pip3 list
```

# 5、pydoc：
```bash
# 查看所有python模块
pydoc modules
pydoc2 modules
pydoc3 modules
```