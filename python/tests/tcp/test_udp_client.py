#!/usr/bin/python3
# python发送udp数据
# 2024-04-26

import sys
import socket

def test_udp_client():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 创建 UDP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # 服务器地址
    server_address = ('192.168.0.2', 4004)

    last_msg = ""
    try:
        while True:
            # 用户输入要发送的消息
            message = input("msg(or 'exit' or 'same'): ")
            if message.lower() == 'exit':
                break
            elif message == 'same' or len(message) == 0:
                print("send: " + last_msg)
                message = last_msg
            else:
                last_msg = message

            # 发送数据
            client_socket.sendto(message.encode(), server_address)

    finally:
        client_socket.close()
        print("client closed")

def main():
    test_udp_client()

if __name__ == '__main__':
    main()
