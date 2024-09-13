# 1、安装Django：

```bash
# ubuntu 16.04, ubuntu 18.04
sudo apt install python3-django
# 查看版本：
django-admin --version
```

# 2、创建项目：

```bash
# django 1.8.7
django-admin startapp helloworld
# django 1.11.11
django-admin startproject helloworld
# 将创建新目录helloworld
cd helloworld
```

# 3、创建用户：

```bash
django-admin startproject helloworld
cd helloworld
python3 manage.py migrate  # 将创建db.sqlite3

python3 manage.py shell
from django.contrib.auth.models import User
user = User.objects.create_user('admin', None, 'admin')
user.save()
Ctrl + D  # 退出python shell

# 或：先手动执行migeate创建db.sqlite3，再动态创建User
```

