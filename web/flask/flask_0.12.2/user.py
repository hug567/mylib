#!/usr/bin/python
# 练习：flask用户
# 时间：2023-11-21

from flask_login import UserMixin  # 引入用户基类
from werkzeug.security import generate_password_hash, check_password_hash

USERS = [
    {
        "id": 1,
        "username": 'admin',
        "password": generate_password_hash('admin')
    },
]

class User(UserMixin):
    """用户类"""
    def __init__(self, user):
        self.username = user.get("username")
        self.password_hash = user.get("password")
        self.id = user.get("id")

    def verify_password(self, password):
        """密码验证"""
        if self.password_hash is None:
            return False
        return check_password_hash(self.password_hash, password)

    def get_id(self):
        """获取用户ID"""
        return self.id

    @staticmethod
    def get(user_id):
        """根据用户ID获取用户实体，为 login_user 方法提供支持"""
        if not user_id:
            return None
        for user in USERS:
            if user.get('id') == user_id:
                return User(user)
        return None