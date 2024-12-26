#!/usr/bin/python3
# python中使用asyncio实现异步延时任务
# 2024-12-26

import sys
import time
import asyncio

async def _delayed_task():
    await asyncio.sleep(3)
    timestr = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
    print('[' + timestr + ']: will finish _delayed_task after sleep(3)')

async def _create_async_task():
    task = asyncio.create_task(_delayed_task())
    await task

def test_async_delay():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    timestr = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
    print('[' + timestr + ']: will run delayed task in call func')

    asyncio.run(_create_async_task())

    timestr = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
    print('[' + timestr + ']: finish run delayed task in call func')

def main():
    test_async_delay()

if __name__ == '__main__':
    main()
