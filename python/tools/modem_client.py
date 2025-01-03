#!/usr/bin/python3
# 模拟猫向主控板发送OpenAMIP消息，用于调试
# 猫的逻辑：
#    1). 猫收到a 5
#          猫以5s间隔给天线回 L 1 1 消息
#    2). 猫收到c 0 0 0 25
#          猫以25Hz的频率通过UDP给天线回 C 3 0 0 0 0 消息
#    3). 猫给天线发送A 15
#          天线将以15s间隔回 s 1 1 0 0 消息
#    4). 猫给天线发送W 5
#          天线将以5s间隔发送w 1 31.8382767 117.1354689 0 0 0 0 0 0 0 0
#    5). 猫收到s 1 1 0 0和w消息后，给天线回对星参数：
#          S 134.0 0.1 0 0
#          P H V
#          H 1508.00 51.750
#          B 9750.00 12800.00
#          F
# 2025-01-02

import os
import sys
import time
import random
import socket
import argparse
import threading

g_args = None
g_sock = None

def log_info(info_str):
    print('[' + time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())) + '] ' + info_str)

def send_C_message_thread(sock, freq):
    interval_ms = 1000 / freq
    while True:
        snr = round(random.random() / 2.0 + 3.0, 4)
        sock.sendall(b'C ' + str.encode(str(snr))  + b' 0 0 0 0')
        time.sleep(interval_ms / 1000.0)

def create_C_thread(sock, freq):
    log_info("will create thread to sendig C message")
    thread = threading.Thread(target=send_C_message_thread, args=(sock, freq))
    thread.start()

def parse_openamip_messages(sock, msg_str):
    log_info(f'receive data: {msg_str}')
    if msg_str[0] == 'c':
        freq = 25
        create_C_thread(sock, freq)

def connect_to_antenna():
    global g_sock
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((g_args.ip, g_args.port))
    g_sock = sock
    sock.sendall(b'A 15\r\n')
    sock.sendall(b'W 5\r\n')
    while True:
            msg = sock.recv(1024)
            if msg == b'':
                log_info(f"connect maybe broken, will close socket")
                break
            parse_openamip_messages(sock, bytes.decode(msg))
    sock.close()

def parse_args(argv):
    global g_args

    parser = argparse.ArgumentParser(description='Modem  client')

    parser.add_argument('-i', '--ip', type=str, default='192.168.0.2',
                        help='antenna ip')
    parser.add_argument('-p', '--port', type=int, default=4002,
                        help='antenna port')
    parser.add_argument('-m', '--modem', type=str, default='default',
                        choices=['default', 'thiss', 'iq200', 'tjyd'],
                        help='modem type')

    g_args = parser.parse_args()

    print('ip:', g_args.ip)
    print('port:', g_args.port)
    print('modem:', g_args.modem)

def main():
    parse_args(sys.argv)
    connect_to_antenna()

if __name__ == '__main__':
    main()
