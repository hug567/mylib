import sys
import paramiko
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton

# 定义事件处理函数
def on_button_clicked():
    print("Button Clicked")

def run_cmd_with_return(cmd):
    transport = paramiko.Transport(("192.168.0.2", 22))
    transport.connect(username="root", password="root")
    ssh = paramiko.SSHClient()
    ssh._transport = transport
    stdin, stdout, stderr = ssh.exec_command(cmd)
    res, err = stdout.read(), stderr.read()
    result = res if res else err
    transport.close()
    return result.decode()

def run_cmd_without_return(cmd):
    result = run_cmd_with_return(cmd)
    print(result)

def zynq_is_alive():
    try:
        transport = paramiko.Transport(("192.168.0.2", 22))
    except:
        print("Can not find zynq board")
        return False
    try:
        transport.connect(username="root", password="root")
    except:
        print("Connect to zynq failed")
        return False
    transport.close()
    return True

def main():
    if not zynq_is_alive():
        exit(1)
    run_cmd_without_return("df -hT")
    #exit(0)


    # 创建应用程序对象
    app = QApplication(sys.argv)
    # 创建主窗口
    window = QMainWindow()
    window.setWindowTitle("zynq update")

    desktop = QApplication.desktop()
    width = 800
    height = 400
    left = int((desktop.width() - width) / 2)
    top = int((desktop.height() - height) / 2)
    window.setGeometry(left, top, width, height)
    # 创建按钮组件
    #button = QPushButton("Click Me", window)
    #button.setGeometry(100, 100, 100, 50)
    # 将事件和事件处理函数绑定起来
    #button.clicked.connect(on_button_clicked)
    # 显示窗口
    window.show()
    # 运行应用程序
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
