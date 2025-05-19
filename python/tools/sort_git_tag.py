#!/usr/bin/python3
# 找出最新commit上最新的tag
# 2024-04-17

import re
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

def get_latest_tag():
    cmd = 'git log --oneline --decorate | head -n 1'
    latest_commit = run_shell_return_result(cmd)[0]
    print(latest_commit)

    tag_dict = {}
    tag_match = re.finditer('tag: ', latest_commit)
    for sub in tag_match:
        end_index=sub.span()[1]
        start_with_tag=latest_commit[end_index:]
        all_tags = run_shell_return_result('git tag')
        for one_tag in all_tags:
            if start_with_tag.find(one_tag) == 0:
                tag_time = get_tag_create_time(one_tag)
                tag_dict[one_tag] = tag_time
                print("tag: [", one_tag, "] tag_time: [", tag_time, "]")

    sorted_tag = dict(sorted(tag_dict.items(), key=lambda x:x[1], reverse=True))
    print("sorted tag by time:", sorted_tag)
    latest_tag = ""
    for key, val in sorted_tag.items():
        latest_tag = key
        break
    return latest_tag

def main():
    latest_tag = get_latest_tag()
    if len(latest_tag) > 0:
        print("latest_tag:", latest_tag)
    else:
        print("no tag in latest commit")

if __name__ == '__main__':
    main()
