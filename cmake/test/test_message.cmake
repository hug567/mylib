# 执行脚本：cmake -P test_message.cmake

# 普通字符串信息
message("[hx-debug] this is a message")

# 打印变量值
message("[hx-debug] CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

# 打印警告信息，将cmake继续执行
message(WARNING "[hx-debug] this is a warning message")

# 打印错误信息，将cmake终止执行
message(FATAL_ERROR "[hx-debug] this is a fatal error message")
