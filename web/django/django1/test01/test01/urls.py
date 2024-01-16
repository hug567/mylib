"""test01 URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin
from . import views
#from session import views as session_views

urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^$', views.index),
    url(r'^index.html$', views.index),
    url(r'^test_form.html$', views.test_form),
    url(r'^test_form_filename$', views.test_form_filename),
    url(r'^test_ajax_read.html$', views.test_ajax_read),

    url(r'^test_ajax_form.html$', views.test_ajax_form),
    # 响应前端ajax请求
    url(r'test_ajax_submit/', views.test_ajax_submit),

    url(r'^test_ajax_loop_read.html$', views.test_ajax_loop_read),
    # ajax将请求的读取时间接口
    url(r'test_ajax_loop_read_date/', views.test_ajax_loop_read_date),

    url(r'^test_login.html$', views.test_login),
    url(r'test_login_ajax/', views.test_login_ajax),

    # ajax页面跳转
    url(r'^test_ajax_jump.html$', views.test_ajax_jump),
    url(r'test_ajax_jump_ajax/', views.test_ajax_jump_ajax),

    # 通过session识别用户
    url(r'^test_session.html$', views.test_session),
    url(r'test_session_login/', views.test_session_login),
    url(r'test_session_logout/', views.test_session_logout),
    url(r'^test_session_page.html$', views.test_session_page),

    # 上传文件
    url(r'^test_upload.html$', views.test_upload),
    url(r'test_ajax_upload/', views.test_ajax_upload),
]
