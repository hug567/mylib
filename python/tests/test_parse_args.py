# python解析命令行参数
# 2024-08-16
import sys
import argparse

def parse_args(argv):
    parser = argparse.ArgumentParser(description='Get student information')

    # 字符串型参数
    parser.add_argument('-n', '--name', type=str, help='supply name')
    # 整形参数
    parser.add_argument('-a', '--age', type=int, help='supply age')
    # 带默认值的整型参数
    parser.add_argument('-w', '--weight', type=int, default=50, help='supply weight')
    # 指定可选值的字符串型参数
    parser.add_argument('-g', '--gender', type=str, default='male', choices=['male', 'female'], help='supply gender')
    args = parser.parse_args()

    print('name:', args.name)
    print('age:', args.age)
    print('weight:', args.weight)
    print('gender:', args.gender)

def main():
    parse_args(sys.argv)

if __name__ == '__main__':
    main()