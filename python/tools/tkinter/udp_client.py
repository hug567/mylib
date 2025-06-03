# python gui程序: udp client
# Create: 2025-05-29 19:49:52

import time
import socket
import threading
import tkinter as tk
from tkinter import messagebox
from tkinter import scrolledtext

g_root = None
g_msg_list = []
g_client_socket = None
g_server_address = None
g_window_closed = False

def udp_send_msg():
    try:
        while True:
            if g_window_closed:
                print(f'window is closed')
                if g_client_socket is not None:
                    g_client_socket.close()
                return
            if g_client_socket is None or g_server_address is None or \
                    len(g_msg_list) == 0:
                time.sleep(0.5)
                continue
            msg_str = g_msg_list.pop(0)
            print(f'will send msg: {msg_str}')
            g_client_socket.sendto(msg_str.encode(), g_server_address)
    finally:
        if g_client_socket is not None:
            g_client_socket.close()
        print("client closed")

def click_connect():
    ip_str = entry_ip.get()
    port = int(entry_port.get())
    global g_client_socket, g_server_address
    g_client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    g_server_address = (ip_str, port)
    print(f'connect to udp sever success: {ip_str}:{port}')

def click_send_msg():
    send_str = send_msg.get('1.0', tk.END).strip()
    if len(send_str) == 0:
        print(f'there is nothing need to send')
        return
    global g_msg_list
    g_msg_list.append(send_str)

def btn_msg_click(btn_id):
    msg_list = ['']
    msg_list.append('TLE#1 62247U 24232L   25138.54005849  .00000189  ' + \
            '00000+0  27457-3 0  9993#2 62247  88.9975  62.3623 0016812  ' + \
            '80.4104 279.8946 13.50953189 71105#E')
    msg_list.append('S#124.383342#64.056237#1067.718682#62247#E')
    msg_list.append('R#1850.000000#10600.000000#E')
    msg_list.append('T#1700.000000#12800.000000#E')
    msg_list.append('P#1#1#0#0#2#1#0#E')

    send_msg.delete('1.0', tk.END)
    if btn_id > 0 and btn_id < len(msg_list):
        send_msg.insert(tk.END, msg_list[btn_id])

def create_elements(root):
    tk.Label(root, text="server ip:").place(x=10, y=10)
    global entry_ip
    entry_ip = tk.Entry(root)
    entry_ip.place(x=10, y=40)
    entry_ip.insert(0, '192.168.0.2')

    tk.Label(root, text="server port:").place(x=10, y=70)
    global entry_port
    entry_port = tk.Entry(root)
    entry_port.place(x=10, y=100)
    entry_port.insert(0, '4004')

    send_btn = tk.Button(root, text="connect", command=click_connect)
    send_btn.place(x=10, y=130)

    for i in range(3):
        first_y = 140
        for j in range(1, 10):
            index = i * 9 + j
            text = f'msg{index:0>2}'
            x = 10 + i * 60
            y = first_y + j * 30
            msg_btn = tk.Button(root, text=text, \
                    command=lambda index=index:btn_msg_click(index))
            msg_btn.place(x=x, y=y)

    g_canvas = tk.Canvas(root, width=100, height=100)
    g_canvas.place(x=30, y=1300)
    g_circle = g_canvas.create_oval(10, 10, 90, 90, fill='red')

    global send_msg
    send_msg = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=80, height=30)
    send_msg.place(x=200, y=10)

    send_btn = tk.Button(root, text="    Send    ", command=click_send_msg)
    send_btn.place(x=450, y=420)

    global log_msg
    log_msg = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=108, height=8)
    log_msg.place(x=10, y=470)

def window_close():
    global g_window_closed
    g_window_closed = True
    g_root.destroy()

def main():
    global g_root

    root = tk.Tk()
    g_root = root

    root.title("UDP Client")
    root.geometry("800x600")

    create_elements(root)

    thread = threading.Thread(target=udp_send_msg)
    thread.start()

    root.protocol("WM_DELETE_WINDOW", window_close)
    root.mainloop()

if __name__ == '__main__':
    main()
