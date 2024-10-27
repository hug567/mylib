# python哈希函数
# 2024-10-27

import sys
import hashlib

# MD5算法：
def test_hash_md5():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    data = 'helloworld'
    data_hash = hashlib.md5(data.encode()).hexdigest()
    print(f'data: {data}')
    print(f'data_hash: {data_hash}')

# SHA1算法
def test_hash_sha1():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    data = 'helloworld'
    data_hash = hashlib.sha1(data.encode()).hexdigest()
    print(f'data: {data}')
    print(f'data_hash: {data_hash}')

# SHA256算法
def test_hash_sha256():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    data = 'helloworld'
    data_hash = hashlib.sha256(data.encode()).hexdigest()
    print(f'data: {data}')
    print(f'data_hash: {data_hash}')

def main():
    test_hash_md5()
    test_hash_sha1()
    test_hash_sha256()

if __name__ == '__main__':
    main()
