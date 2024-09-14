# 自定义标签和过滤器
# 1、根目录创建目录templagetgas目录，目录名称不能自定义
# 2、templagetgas创建tag文件，名称可自定义，如：my_tags.py
# 3、在settings.py中TEMPLATES变量中配置自定义标签
# 2024-09-14

from django import template

register = template.Library()

# 自定义一个标签
# 使用前需在html的body最上方导入此tag文件：{% load my_tags %}
@register.simple_tag
def has_permission_admin():
    return True