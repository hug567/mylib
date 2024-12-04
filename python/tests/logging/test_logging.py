# python日志模块
# 2024-11-14

import os
import logging
from logging.handlers import RotatingFileHandler
import other

# 设置日志记录器，日志记录器的名称可自定义
logger = logging.getLogger(__name__)

def test_logging():
    # 限制单文件大小1M，历史保留最多5个文件
    handler = RotatingFileHandler('/tmp/python.log', maxBytes=1024*1024, backupCount=5)
    # 日志记录格式
    formatter = logging.Formatter('[%(asctime)s][%(levelname)-8s][%(filename)s:%(lineno)d] %(message)s')
    handler.setFormatter(formatter)
    logger.setLevel(logging.INFO)
    logger.addHandler(handler)

    logger.info("this is an info log 1")
    logger.info("this is an info log 2")
    logger.info("this is an info log 3")
    logger.info("this is an info log 4")
    logger.info("this is an info log 5")
    logger.info("this is an info log 6")
    logger.warning("this is a warning log")
    logger.error("this is an error log")
    logger.critical("this is an critical log")

    for i in range(0, 3):
        logger.info(f'this is an info log: {i}')

# 调用定义在另一个文件中的函数，在另一个文件中使用logger记录日志
def test_logging_other():
    # 调用子文件中的函数，其会使用主程序中的日志记录器记录日志
    other.write_log()

def main():
    test_logging()
    test_logging_other()

if __name__ == '__main__':
    main()
