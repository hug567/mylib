#!/usr/bin/python3
################################################################################
# learinig list
# python 3.6.9
# 2023-09-01
################################################################################

import sys

def test_define_list():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

def main():
    test_define_list()

if __name__ == '__main__':
    main()
