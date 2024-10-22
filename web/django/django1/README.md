# 1、安装django：
```bash
# ubuntu 16.04, ubuntu 18.04
sudo apt install python3
sudo apt install python3-django
# Windows安装django：
pip install Django
# 查看版本：
django-admin --version
```

# 2、创建django项目：

```bash
# django 1.8.7
django-admin startapp helloworld
# django 1.11.11
django-admin startproject helloworld
# 将创建新目录helloworld
cd helloworld
```

# 3、基本设置：

```bash
# hellowrold/helloworld/settings.py
#--------------------------------------------------------#
# 允许所有ip打开网站，将ALLOWED_HOSTS修改为：
ALLOWED_HOSTS = ["*"]
#--------------------------------------------------------#
```

# 4、运行网站：

```bash
# 创建数据库文件：
python3 manage.py migrate
# 启动网站：
python3 manage.py runserver 0.0.0.0:9100
```

# 5、创建第一个页面：

```bash
# 创建html文件放置目录：
cd helloworld
mkdir templates
cd templates
# 创建html文件并写入内容：
touch index.html

# 配置hellowrold/helloworld/settings.py：
#--------------------------------------------------------#
TEMPLATES = [
            'DIRS': [os.path.join(BASE_DIR, 'templates')],
]
#--------------------------------------------------------#

# 新建hellowrold/helloworld/views.py
#--------------------------------------------------------#
from django.shortcuts import render, redirect

def index(request):
    context = {}
    return render(request, 'index.html', context)
#--------------------------------------------------------#

# 配置urls.py：
#--------------------------------------------------------#
from . import views

urlpatterns = [
    url(r'^$', views.index),
    url(r'^index.html$', views.index),
]
#--------------------------------------------------------#
```

# 6、在数据库中创建用户：

```bash
if not User.objects.filter(username='admin').exists():
    User.objects.create_user('admin', None, 'Rhosoon')
```