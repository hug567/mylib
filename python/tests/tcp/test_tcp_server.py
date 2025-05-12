#!/usr/bin/python3
# python创建tcp server
# Create: 2025-05-09 09:28:04

import socket

def tcp_server():
    # 创建 socket
    #   AF_INET: ipv4
    #   SOCK_STREAM: tcp
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    host = '0.0.0.0'  # 监听所有可用接口
    port = 12345
    # 绑定到主机和端口
    server_socket.bind((host, port))
    # 允许端口复用
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    # 开始监听，最多允许的连接数为 5
    server_socket.listen(5)

    try:
        while True:
            # 接受客户端连接
            client_socket, client_address = server_socket.accept()
            print(f"accept from: {client_address}")

            try:
                while True:
                    # 接收数据（最大1024字节）
                    data = client_socket.recv(1024).decode()
                    print(f"received: [{data}]")
                    # 发送响应
                    response = f"already received: {data}"
                    client_socket.send(response.encode())
            except ConnectionResetError:
                print(f'client close: {client_address}');
            except BrokenPipeError:
                print(f'client close: {client_address}');
            finally:
                client_socket.close()

    except KeyboardInterrupt:
        print(f"server close")
    finally:
        server_socket.close()

def main():
    tcp_server()

if __name__ == '__main__':
    main()
