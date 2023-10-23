import os
from django.shortcuts import render
from django.http import HttpResponse

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