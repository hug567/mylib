#!/usr/bin/python3

import sys
import django
django.setup()
from django.contrib.auth.models import User
from django.contrib.auth.models import Group

def user_exist(name):
    users = User.objects.all()
    for user in users:
        if user.username == name:
            return True
    return False

def create_user(name, email, password):
    if user_exist(name):
        return
    print("will create user:", name)
    user = User.objects.create_user(name, email, password)
    user.save()

def group_exist(name):
    groups = Group.objects.all()
    for group in groups:
        if name == group.name:
            return True
    return False

def create_group(name):
    if group_exist(name):
        return
    print("will create group:", name)
    group = Group.objects.create(name=name)
    group.save()

def main():
    create_group("normal")
    create_group("admin")
    create_group("root")

    create_user("normal", "normal@example.com", "normal")
    create_user("admin", "admin@example.com", "admin")
    create_user("root", "root@example.com", "rootroot")

    users = User.objects.all()
    for user in users:
        print("user:", user.username)

    groups = Group.objects.all()
    for group in groups:
        print("group:", group.name)

if __name__ == '__main__':
    main()
