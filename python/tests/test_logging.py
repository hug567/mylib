# python日志模块
# 2024-11-14

import os
import logging
from logging.handlers import RotatingFileHandler

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

    for i in range(0, 100000):
        logger.info(f'this is an info log: {i}')

def main():
    test_logging()

if __name__ == '__main__':
    main()
