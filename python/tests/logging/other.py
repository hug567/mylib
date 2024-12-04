# 当前是子文件，主程序文件会调用子文件中的函数，同时子文件中函数使用主程序中的
# loggger记录日志
# 2024-12-04

import logging

# 获取主程序中的日志记录器，日志记录器的名称可自定义
logger = logging.getLogger('__main__')

def write_log():
    print('Enter other.py write_log')
    # 使用主程序中的日志记录器记录日志到文件
    logger.info('there is a log in other.py')
