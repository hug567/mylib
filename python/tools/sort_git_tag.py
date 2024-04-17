#!/usr/bin/python3
# 找出最新commit上最新的tag
# 2024-04-17

import os
import re
import sys
import subprocess

def run_shell_return_result(cmd):
    output = []
    # run shell cmd
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    # realtime output
    while True:
        line = p.stdout.readline()
        if not line:
            break
        output.append(line.strip().decode('utf-8'))
    # wait for the shell cmd to finish
    p.wait()
    return output

def get_tag_create_time(tag):
    cmd = "git show " + tag + " --date=raw | head -n 5 | grep Date: | head -n 1 | awk '{print$2}'"
    tag_time = run_shell_return_result(cmd)[0]
    return tag_time

def sort_git_tag():
    cmd = 'git log --oneline --decorate | head -n 1'
    latest_commit = run_shell_return_result(cmd)[0]
    print(latest_commit)
    tag_match = re.finditer('tag: ', latest_commit)
    for sub in tag_match:
        end_index=sub.span()[1]
        #print("end_index:", end_index)
        start_with_tag=latest_commit[end_index:]
        all_tags = run_shell_return_result('git tag')
        for one_tag in all_tags:
            if start_with_tag.find(one_tag) == 0:
                print("tag:", one_tag)
                tag_time = get_tag_create_time(one_tag)
                print("tag_time:", tag_time)

def main():
    sort_git_tag()

if __name__ == '__main__':
    main()
