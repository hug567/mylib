# python格式化字符串
# 2024-10-27

import sys

# f-string格式化字符串
def test_format_f():
    print(sys._getframe().f_code.co_name, ': -------------------------', sep='')

    name = 'Tom'
    age = 18
    print(f'name: {name}, age: {age}')

# %格式化字符串
def test_format_percent():
    print(sys._getframe().f_code.co_name, ': -------------------------', sep='')

    name = 'Bob'
    age = 19
    print('name: %s, age: %d' % (name, age))

# str.format格式化字符串
def test_format_str():
    print(sys._getframe().f_code.co_name, ': -------------------------', sep='')

    name = 'Jerry'
    age = 20
    print('name: {}, age: {}'.format(name, age))

def main():
    test_format_f()
    test_format_percent()
    test_format_str()

if __name__ == '__main__':
    main()
