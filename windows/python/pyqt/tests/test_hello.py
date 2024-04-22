import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton

# 创建应用程序对象
app = QApplication(sys.argv)

# 创建主窗口
window = QMainWindow()
window.setWindowTitle("My Window")
window.setGeometry(100, 100, 400, 300)

# 创建按钮组件
button = QPushButton("Click Me", window)
button.setGeometry(100, 100, 100, 50)

# 定义事件处理函数
def on_button_clicked():
    print("Button Clicked")

# 将事件和事件处理函数绑定起来
button.clicked.connect(on_button_clicked)

# 显示窗口
window.show()

# 运行应用程序
sys.exit(app.exec_())