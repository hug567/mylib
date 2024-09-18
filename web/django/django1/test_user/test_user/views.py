import os
import json
from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.http import JsonResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import permission_required
from django.contrib.auth.models import Permission
from django.contrib.contenttypes.models import ContentType
from test_user.models import TestUser

def mylogin(request):
    context = {}
    if request.GET:
        context["nextURL"] = request.GET.get('next')
    return render(request, 'login.html', context)

def mylogin_submit(request):
    dict = {}
    if request.POST:
        username = request.POST["Username"]
        password = request.POST["Password"]
        nexturl = request.POST["nextURL"]
        if len(nexturl) == 0:
            nexturl = "index.html"
        print("[INFO] nexturl: %s" % nexturl)
        print("[INFO] username: [", username, "], password: [", password, "]", sep='')
        user = authenticate(username=username, password=password)
        if user is not None:
            print("[INFO] get user success, will login")
            login(request, user)
            dict["Jump"] = nexturl
            request.session.set_expiry(0)
        else:
            print("[INFO] Username or Password error")
            dict["Info"] = "Username or Password error"
    else:
        dict["Info"] = "Error: not get POST request"
    return HttpResponse(json.dumps(dict))

def mylogout_submit(request):
    dict = {}
    if request.POST:
        logout(request)
        dict["Jump"] = "login.html"
    else:
        dict["Info"] = "Error: not get POST request"
    return HttpResponse(json.dumps(dict))

# 要求有具体的权限才可访问：
# @login_required
@permission_required('test_user.normal')
# @permission_required('test_user.admin')
def index(request):
    context = {}
    user = request.user
    context["User"] = str(user)
    if str(user) == 'admin':
        context['isAdmin'] = True
    print("[INFO] current user:", str(user), "， type(user):", type(user))
    return render(request, 'index.html', context)

def _create_permission_by_codename(codename):
    content_type = ContentType.objects.get_for_model(TestUser)
    # 先判断是否已创建了权限
    all_permissions = Permission.objects.all()
    for perm in all_permissions:
        if perm.codename == codename:
            # 已有则直接返回
            print("[INFO] permission", codename, "already exists")
            return perm
    # 若没有则新建
    print("[INFO] will create permission:", codename)
    perm = Permission.objects.create(
        codename = codename,
        name = codename,
        content_type = content_type,
    )
    return perm

def _create_user_with_permissions(username, *perms):
    # 创建用户
    user = None
    if not User.objects.filter(username=username).exists():
        print("[INFO] will create user:", username)
        user = User.objects.create_user(username, None, username)
    else:
        all_users = User.objects.all()
        for user in all_users:
            if user.get_username() == username:
                print("[INFO] user", str(user), "alerady exists")
                break
    if user is not None:
        # 给用户添加权限，可添加多个权限
        for perm in perms:
            if not user.has_perm(perm):
                print("[INFO] will add perm", perm.codename, "to user", username)
                user.user_permissions.add(perm)
        user.save()
    return user

def main():
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    db_file = os.path.join(base_dir, 'db.sqlite3')
    # 无数据库文件时不能判断用户是否存在
    if not os.path.exists(db_file):
        print("[WARN] there is no sqlite file")
        return

    # 创建权限
    perm_normal = _create_permission_by_codename("normal")
    perm_admin = _create_permission_by_codename("admin")

    _create_user_with_permissions("normal", perm_normal)
    _create_user_with_permissions("admin", perm_normal, perm_admin)

main()
