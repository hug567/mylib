#!/usr/bin/python
# 练习：flask后端python代码
# 时间：2023-11-07

import json
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
@app.route('/index.html')
def index():
    return render_template('index.html')

# 练习：ajax提交表单
@app.route('/test_ajax_form.html')
def test_ajax_form():
    return render_template('test_ajax_form.html')
# 响应ajax提交
@app.route('/test_ajax_submit_01/', methods=['GET', 'POST'])
def test_ajax_submit_01():
    print("[hx-debug] Enter test_ajax_submit_01")
    if request.method == 'POST':
        name = request.form.get('Name')
        if name is not None:
            print("name: %s" % name)
    else:
        print("Does not get a POST request")
    # 返回普通数据
    return "Enter test_ajax_submit_01"
# 响应ajax提交
@app.route('/test_ajax_submit_02/', methods=['GET', 'POST'])
def test_ajax_submit_02():
    print("[hx-debug] Enter test_ajax_submit_02")
    data = {
        'Log' : "Enter test_ajax_submit_02",
    }
    #data['Log'] = "Enter test_ajax_submit_02"
    # 返回json数据
    return json.dumps(data)

# 练习：flask模板
@app.route('/test_template.html')
def test_template():
    return render_template('test_template.html')