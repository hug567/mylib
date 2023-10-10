#!/usr/bin/python3
################################################################################
# python练习：run cmd in remote server by ssh
# python版本：python 3.6.9
# 时间：2023-09-11
################################################################################
import paramiko

def run_cmd_in_remote(_host_ip, _username, _password, _cmd):
    try:
        _ssh_fd = paramiko.SSHClient()
        _ssh_fd.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        _ssh_fd.connect(_host_ip, username = _username, password = _password)
    except Exception as e:
        print('ssh %s@%s: %s' % (_username, _host_ip, e))
        return ""

    stdin,stdout,stderr = _ssh_fd.exec_command(_cmd)
    result = ""
    for line in stdout.readlines():
        result += line
    _ssh_fd.close()

    return result

def find_line(lines, key_word):
    try:
        line_index = lines.index(key_word)
        line_start = lines.rfind("\n", 0, line_index) + 1
        line_end = lines.find("\n", line_index)
        line = lines[line_start:line_end]
        return line
    except ValueError:
        print("line not found")
        return ""

def main():
    ret = run_cmd_in_remote("10.110.0.10", "root", "root", "configinfo")
    line = find_line(ret, "TxIFFreq")
    print(line)
    TxIFFreq = float(line.split()[-1])
    print(TxIFFreq)
    if TxIFFreq == 1200.0:
        print("set TxIFFreq to 1200 success")
    else:
        print("set TxIFFreq to 1200 failed")


if __name__ == "__main__":
    main()
