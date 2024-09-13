import os
import json
from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.http import JsonResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import permission_required

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
#@login_required
#@permission_required('test_user.normal')
#@permission_required('test_user.admin')
@permission_required('test_user.root')
def index(request):
    context = {}
    return render(request, 'index.html', context)

def main():
    # return
    # 在数据库中创建两个用户：user/user, admin/admin
    if not User.objects.filter(username='user').exists():
        print("thier is no user: user")
        # User.objects.create_user('user', None, 'user')
    # if not User.objects.filter(username='admin').exists():
        # User.objects.create_user('admin', None, 'admin')

main()