#!/usr/bin/python3

from django.contrib.auth.models import User

users = User.objects.all()
for user in users:
    print(user.username)
