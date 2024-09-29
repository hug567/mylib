#!/usr/bin/python3
################################################################################
# python练习：run cmd in remote server by ssh
# python版本：python 3.6.9
# 时间：2023-09-11
################################################################################
import paramiko

################################################################################

class SSHRemote():
    # 构造函数
    def __init__(self, username, ip, password):
        self.username = username
        self.ip = ip
        self.password = password

    # 在远程机器中执行命令并返回结果
    def run_cmd(self, _cmd):
        try:
            _ssh_fd = paramiko.SSHClient()
            _ssh_fd.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            _ssh_fd.connect(self.ip, username = self.username,
                            password = self.password)
        except Exception as e:
            print('ssh %s@%s: %s' % (self.username, self.ip, e))
            return ""
        stdin,stdout,stderr = _ssh_fd.exec_command(_cmd)
        exit_status = stdout.channel.recv_exit_status()
        if exit_status == 0:
            result = stdout
        else:
            result = stderr
        result_str = ""
        for line in result.readlines():
            result_str += line
        _ssh_fd.close()
        return result_str.strip()

    # 执行前打印将执行的命令
    def run_cmd_echo(self, _cmd):
        print("will run cmd in remote:", _cmd)
        return self.run_cmd(_cmd)

################################################################################

def test_run_cmd_in_remote():
    print("test_run_cmd_in_remote: -------------------------------------------")

    remote = SSHRemote("root", "192.168.0.2", "root")
    print(remote.run_cmd('uname -a'))
    print(remote.run_cmd_echo('ls -l /'))
    print(remote.run_cmd_echo('ls /xx'))

def main():
    test_run_cmd_in_remote()

if __name__ == "__main__":
    main()
