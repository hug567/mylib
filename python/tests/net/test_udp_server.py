#!/usr/bin/env python3
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("192.168.0.2", 4004))
print("UDP bound on port 4004...")

while True:
    data, addr = s.recvfrom(1024)
    print(bytes.decode(data))
