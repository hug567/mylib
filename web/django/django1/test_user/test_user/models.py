# django自定义模型
# 2024-03-06

from django.db import models

class TestUser(models.Model):
    name = models.CharField(max_length=20)
