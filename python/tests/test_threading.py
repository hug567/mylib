#!/usr/bin/python3
# python创建线程
# 2024-12-26


import sys
import time
import threading

def log_info(log_str):
    timestr = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
    print('[' + timestr + ']: ' + log_str)

# 线程处理函数
def _thread_func():
    time.sleep(3)
    log_info('will finish _delayed_task after sleep(3)')

# 创建线程
def test_create_thread():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    log_info('will create thread')
    thread = threading.Thread(target=_thread_func)
    thread.start()
    log_info('finish create thread')

    # 等待线程执行结束
    thread.join()
    time.sleep(1)
    log_info('all thread done')

def main():
    test_create_thread()

if __name__ == '__main__':
    main()
