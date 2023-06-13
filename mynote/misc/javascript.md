## JavaScript入门

### 1、win10安装nodejs：

下载LTS版本安装包并安装：https://nodejs.org/en/ 

<img src="../pictures/javascript/01.png" style="zoom:80%" div align=center />

打开cmd测试是否安装成功：

```shell
node -v                 # 查看node版本
npm -v                  # 查看npm版本
```

新建nodejs数据保存路径：F:\Program Files\nodejs\node_cache

​                                               F:\Program Files\nodejs\node_data

​                                               F:\Program Files\nodejs\node_data\node_modules

在cmd中指定存储路径：

```shell
npm config                                                     # 查看使用帮助
npm config list                                                # 查看当前配置
npm config set cache "F:\Program Files\nodejs\node_cache"      # 设置缓存目录
npm config set prefix "F:\Program Files\nodejs\node_data"      # 设置全局包目录
```

设置系统变量： 我的电脑 > 右键 > 属性 > 高级系统设置 > 高级 > 环境变量 

新建系统变量NODE_PATH，并设置为：

```shell
F:\Program Files\nodejs\node_data\node_modules
```

### 2、运行JavaScript：

#### 2.1、在html中执行JavaScript指令：

新建文件index.html并写入：

```html
<!DOCTYPE html>
<html>
    <head>
        <title>This is my first page</title>
    </head>
    <body>
        <script>
            document.write("hello word");
        </script>
    </body>
</html>
```

在\<script> ...\</script>中编写JavaScript指令，然后使用浏览器打开index.html。

<span><div style="text-align: center">![Picture](pictures/javascript/02.png)</div></span>

#### 2.2、在html中执行JavaScript脚本：

* index.html：

```html
<!DOCTYPE html>
<html>
    <head>
        <title>This is my first page</title>
    </head>
    <body>
        <script>
            document.write("hello world" + "<br/>");
        </script>
        <script type="text/javascript" src="helloworld.js"></script>
    </body>
</html>
```

* helloworld.js：

```javascript
document.write("current code is in helloworld.js" + "<br/>");
```

<span><div style="text-align: center">![Picture](pictures/javascript/03.png)</div></span>







