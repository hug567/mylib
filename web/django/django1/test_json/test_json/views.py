import os
import json
from collections import OrderedDict
from django.shortcuts import render, redirect

def index(request):
    context = {}
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    list_file = os.path.join(base_dir, 'templates/test01.json')

    # 将json文件读取为字典，可能会重新排序
    list_dict_orgin = {}
    with open(list_file, 'r', encoding='utf-8') as file:
        list_dict_orgin = json.load(file)

    # 将json文件读取为未排序的字典
    list_dict_ordered = {}
    with open(list_file, 'r', encoding='utf-8') as file:
        # 使用OrderdDict保证从json文件读取的内容在字典中不被重新排序
        list_dict_ordered = json.load(file, object_pairs_hook=OrderedDict)

    # 将json文件读取为字符串
    with open(list_file, 'r', encoding='utf-8') as file:
        file_str = file.read()
    # 换行符替换为空格
    file_str = file_str.replace('\n', ' ').replace('\r', ' ')
    # 多个空格合并为一个空格
    file_str = ' '.join(file_str.split())

    print("[INOF] list_dict_orgin:", list_dict_orgin)
    print("[INOF] list_dict_ordered:", list_dict_ordered)
    print("[INOF] dict(list_dict_ordered):", dict(list_dict_ordered))
    print("[INOF] file_str:", file_str)

    context['JsonFileDictOrigin'] = list_dict_orgin
    context['JsonFileDictOrdered'] = list_dict_ordered
    context['JsonFileStr'] = file_str

    return render(request, 'index.html', context)