#!/usr/bin/python3

import sys
import django
django.setup()
from test_user.models import TestUser
from django.contrib.auth.models import User
from django.contrib.auth.models import Group
from django.contrib.auth.models import Permission
from django.contrib.contenttypes.models import ContentType

def get_user_by_name(name):
    users = User.objects.all()
    for user in users:
        if user.username == name:
            return user
    return None

def user_exist(name):
    if get_user_by_name(name) is not None:
        return True
    return False

def create_user(name, email, password):
    if user_exist(name):
        return
    print("will create user:", name)
    user = User.objects.create_user(name, email, password)
    user.save()

def create_users():
    create_user("normal", "normal@example.com", "normal")
    create_user("admin", "admin@example.com", "admin")

def get_group_by_name(name):
    groups = Group.objects.all()
    for group in groups:
        if name == group.name:
            return group
    return None

def group_exist(name):
    if get_group_by_name(name) is not None:
        return True
    return False

def create_group(name):
    if group_exist(name):
        return
    print("will create group:", name)
    group = Group.objects.create(name=name)
    group.save()

def create_groups():
    create_group("normal")
    create_group("admin")
    create_group("root")

def add_one_user_to_group(username, groupname):
    user = get_user_by_name(username)
    group = get_group_by_name(groupname)
    if user is not None and group is not None:
        print("will add user", user.username, "to group", group.name)
        user.groups.add(group)

def add_users_to_groups():
    add_one_user_to_group("normal", "normal")
    add_one_user_to_group("admin", "admin")
    add_one_user_to_group("root", "root")

def create_permissions():
    content_type = ContentType.objects.get_for_model()
    perm_normal = Permission.objects.create(
        codename = 'normal',
        name = 'normal user',
        content_type = content_type,
    )
    perm_admin = Permission.objects.create(
        codename = 'admin',
        name = 'admin user',
        content_type = content_type,
    )
    perm_root = Permission.objects.create(
        codename = 'root',
        name = 'root user',
        content_type = content_type,
    )

def get_permission_by_name(name):
    all_permissions = Permission.objects.all()
    for perm in all_permissions:
        if perm.codename == name:
            return perm
    return None

def add_one_perm_to_group(permname, groupname):
    perm = get_permission_by_name(permname)
    group = get_group_by_name(groupname)
    if perm is not None and group is not None:
        print("will add permission", perm.codename, "to group", group.name)
        group.permissions.add(perm)

def add_permissions_to_groups():
    add_one_perm_to_group("normal", "normal")
    add_one_perm_to_group("normal", "admin")
    add_one_perm_to_group("admin", "admin")
    add_one_perm_to_group("normal", "root")
    add_one_perm_to_group("admin", "root")
    add_one_perm_to_group("root", "root")

#------------------------------------------------------------------------------#
def print_all_users_in_group(group):
    users = group.user_set.all()
    for user in users:
        print("    user:", user.username)

def print_all_permissions_in_group(group):
    permissions = group.permissions.all()
    for perm in permissions:
        print("    permission:", perm.codename)

def print_all_info():
    users = User.objects.all()
    for user in users:
        print("user:", user.username)

    groups = Group.objects.all()
    for group in groups:
        print("group:", group.name)
        print_all_users_in_group(group)
        print_all_permissions_in_group(group)

    permissions = Permission.objects.all()
    for perm in permissions:
        print("permission:", perm.codename)

def test_group_has_permission(groupname, permname):
    group = get_group_by_name(groupname)
    if group is None:
        print("get group by name", groupname, "failed")
        return
    permissions = group.permissions.all()
    for perm in permissions:
        if perm.codename == permname:
            print("group", group.name, "has permission", permname)
            return
    print("group", group.name, "has not permission", permname)

def test_user_has_permission(username, permname):
    user = get_user_by_name(username)
    if user is None:
        print("get user by username", username, "failed")
        return
    if user.has_perm("test_user." + permname):
        print("user", user.username, "has permission", permname)
    else:
        print("user", user.username, "has not permission", permname)

def test_user_and_group_permissions():
    test_group_has_permission('normal', 'normal')
    test_group_has_permission('normal', 'admin')
    test_group_has_permission('normal', 'root')
    test_group_has_permission('admin', 'normal')
    test_group_has_permission('admin', 'admin')
    test_group_has_permission('admin', 'root')
    test_group_has_permission('root', 'normal')
    test_group_has_permission('root', 'admin')
    test_group_has_permission('root', 'root')

    test_user_has_permission('normal', 'normal')
    test_user_has_permission('normal', 'admin')
    test_user_has_permission('normal', 'root')
    test_user_has_permission('admin', 'normal')
    test_user_has_permission('admin', 'admin')
    test_user_has_permission('admin', 'root')
    test_user_has_permission('root', 'normal')
    test_user_has_permission('root', 'admin')
    test_user_has_permission('root', 'root')

def main():
    create_groups()
    create_users()
    add_users_to_groups()
    create_permissions()
    add_permissions_to_groups()

    print_all_info()
    test_user_and_group_permissions()

if __name__ == '__main__':
    main()
