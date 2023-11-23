#!/usr/bin/python
# 练习：flask后端python代码
# 时间：2023-11-07

import json
from flask import Flask, render_template, request, url_for #, session
from flask_login import LoginManager, login_user, logout_user, login_required
from user import User

# 默认加载tempates目录中的html，也可自定义
# app=Flask（__name__，template_folder='xxx' ）
app = Flask(__name__)

app.secret_key = 'admin'  # 设置表单交互密钥
login_manager = LoginManager()  # 实例化登录管理对象
login_manager.init_app(app)  # 初始化应用
login_manager.login_view = 'mylogin'  # 设置用户登录视图函数 endpoint

@login_manager.user_loader  # 定义获取登录用户的方法
def load_user(user_id):
    return User.get(user_id)

#------------------------------------------------------------------------------#
# 登录页面
@app.route('/test_login.html')
def mylogin():
    return render_template('test_login.html')
# 登录页面ajax提交
@app.route('/mylogin_submit/', methods=['GET', 'POST'])
def mylogin_submit():
    print("[hx-debug] Enter mylogin_submit")
    dict = {}
    #nexturl = request.args.get('next', '')
    if request.method == 'POST':
        username = request.form.get('Username')
        password = request.form.get('Password')
        print("username: %s, password: %s" % (username, password))
        nexturl = request.args.get('next')
        #nexturl = request.form.get('next')
        #nexturl = session.get('next')
        print("[INFO] ", nexturl)
        if nexturl is None or len(nexturl) == 0:
            print("[INFO] Does not get nexturl, will set to default index.html")
            nexturl = "index.html"
        print("[INFO] nexturl: %s" % nexturl)
        user = User.get(1)
        if user is not None:
            print("user 1 name: %s" % user.username)
            print("user 1 password_hash: %s" % user.password_hash)
            if username == user.username and user.verify_password(password):
                login_user(user)
                dict["Jump"] = "index.html"
                return json.dumps(dict)
    dict["Info"] = "Username or Password error"
    return json.dumps(dict)

#------------------------------------------------------------------------------#
# 登出页面
@app.route('/test_logout.html')
def mylogout():
    return render_template('test_logout.html')
# 登出页面ajax提交
@app.route('/mylogout_submit/', methods=['POST'])
def mylogout_submit():
    print("[hx-debug] Enter mylogout_submit")
    dict = {}
    if request.method == 'POST':
        logout_user()
        dict["Jump"] = "test_login.html"
        return json.dumps(dict)
    dict["Info"] = "Logout failed"
    return json.dumps(dict)

#------------------------------------------------------------------------------#
# 主页面
@app.route('/')
@app.route('/index.html')
@login_required # 需登录才能访问
def index():
    return render_template('index.html')

#------------------------------------------------------------------------------#
# ajax提交表单
@app.route('/test_ajax_form.html')
@login_required # 需登录才能访问
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

#------------------------------------------------------------------------------#
# flask模板
@login_required # 需登录才能访问
@app.route('/test_template.html')
def test_template():
    return render_template('test_template.html')

#------------------------------------------------------------------------------#
# 使用本地静态js/css文件
@login_required # 需登录才能访问
@app.route('/test_static.html')
def test_static():
    return render_template('test_static.html')