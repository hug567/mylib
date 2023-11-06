import os
import json
from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.http import JsonResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout

@login_required
def homepage(request):
    pass

def index(request):
    context = {}
    return render(request, 'index.html', context)

def test_form(request):
    context = {}
    context["djFileContent"] = "xxxxxxx"
    return render(request, 'test_form.html', context)

def test_form_filename(request):
    context = {}
    if request.POST:
        file_name = request.POST["Filename"]
        file_content = os.popen("cat " + file_name).read().strip()
        context["djFileContent"] = file_content
    return render(request, 'test_form.html', context)

def test_ajax_read(request):
    context = {}
    return render(request, 'test_ajax_read.html', context)

def test_ajax_form(request):
    context = {}
    print("[hx-debug] Enter test_ajax_form")
    return render(request, 'test_ajax_form.html', context)

# 响应ajax请求
def test_ajax_submit(request):
    context = {}
    print("[hx-debug] Enter test_ajax_submit")
    if request.POST:
        name = request.POST["Name"]
        print("[hx-debug] name: " + name)
    # 返回请求数据
    return HttpResponse("get name from web: " + name)

def test_ajax_loop_read(request):
    context = {}
    return render(request, 'test_ajax_loop_read.html', context)

def test_ajax_loop_read_date(request):
    date_str = os.popen("date ").read().strip()
    return HttpResponse(date_str)

# 练习：登录界面
def test_login(request):
    context = {}
    return render(request, 'test_login.html', context)
def test_login_ajax(request):
    dict = {}
    if request.POST:
        username = request.POST["Username"]
        password = request.POST["Password"]
        if username == "admin" and password == "admin":
            dict["Username"] = username
            dict["Password"] = password
            dict["Jump"] = "index.html"
        else:
            dict["Info"] = "Username or Password error"
    else:
        dict["Info"] = "not get POST request"
    # 返回JSON字典, js中解析：JSON.parse()
    return HttpResponse(json.dumps(dict))

# 练习：ajax页面跳转
def test_ajax_jump(request):
    context = {}
    return render(request, 'test_ajax_jump.html', context)
def test_ajax_jump_ajax(request):
    if request.POST:
        href = "index.html"
    else:
        href = "not get POST request"
    return HttpResponse(href)

# 练习：通过session识别用户
def test_session(request):
    context = {}
    if not User.objects.filter(username='admin').exists():
        # 创建用户
        User.objects.create_user('admin', None, 'admin')
    return render(request, 'test_session.html', context)
def test_session_login(request):
    dict = {}
    if request.POST:
        username = request.POST["Username"]
        password = request.POST["Password"]
        user = authenticate(username=username, password=password)
        if user is not None:
            login(request, user)
            dict["Jump"] = "index.html"
            # 关闭浏览器session就失效
            request.session.set_expiry(0)
        else:
            dict["Info"] = "Username or Password error"
    else:
        dict["Info"] = "Error: not get POST request"
    return HttpResponse(json.dumps(dict))
# 退出登录
def test_session_logout(request):
    dict = {}
    if request.POST:
        logout(request)
        dict["Jump"] = "test_session.html"
    else:
        dict["Info"] = "Error: not get POST request"
    return HttpResponse(json.dumps(dict))
# 普通页面，访问前通过session判断是否已登录
# 使用装饰器判断用户是否登录
@login_required
def test_session_page(request):
    user = authenticate(username='admin', password='admin')
    if user is not None:
        print("[hx-debug] user exist")
    else:
        print("[hx-debug] user does not exist")
    return render(request, 'test_session_page.html')