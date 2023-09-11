#!/bin/python3

import socket

def main():

    # 服务器的IP地址
    host = '127.0.0.1'
    # 服务器的端口号
    port = 1234

    # 创建一个 TCP 套接字
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        messages = [
                "Hello, I'm Tom\n",
                "Hello, I'm Jerry\n",
                "How are you\n",
                "I'm fine\n",
                "Thank you, and you\n",
                "I'm fine too\n",
        ]
        # 连接到服务器
        client_socket.connect((host, port))
        for msg in messages:
            print(msg)
            client_socket.sendall(msg.encode())
        #data = client_socket.recv(1024)
        #print(f"服务器响应: {data.decode('utf-8')}")
    except Exception as e:
        print("Error:", e)
    finally:
        # 关闭套接字
        client_socket.close()

if __name__ == "__main__":
    main()
