import os
from django.shortcuts import render

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
    return render(request, 'test_ajax_form.html', context)

def test_ajax_submit(request):
    context = {}
    print("[hx-debug] Enter test_ajax_submit")
    return render(request, 'test_ajax_form.html', context)