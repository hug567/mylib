## 1、在Windows中安装python：

```c
https://www.python.org/downloads/windows/                //python下载地址
/* 安装成功后再cmd中验证： */
python --version      //查看python版本
```

## 2、安装openpyxl：

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

## 3、Linux选择python版本：

```shell
# 查看python软连接指向文件：
ls -l /usr/bin/python /usr/bin/python2 /usr/bin/python3

# 添加链接管理：
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1 # 优先级为1
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.6 2 # 优先级为2

# 查看管理的python链接：
sudo update-alternatives --display python

# 选择python版本：
sudo update-alternatives --config python
```

## 4、pip：

```shell
# 升级pip
python -m pip install --upgrade pip
# 查看已安装的python包
pip list
# 安装python包
pip install xxx
```

## 5、pydoc：
```bash
# 查看所有python模块
pydoc modules
pydoc2 modules
pydoc3 modules
```