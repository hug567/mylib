#!/usr/bin/python3
################################################################################
# learinig string
# python 3.6.9
# 2023-05-15
################################################################################
import re
import sys

def test_define_string():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    str01 = "Huang Xing"
    print("str01:", str01)
    # 字符串长度
    print("str01 length:", len(str01))
    # access single char
    print("str01[0]:", str01[0])
    # cut string: start from 1, end before 5 (string index start from 0)
    print("str01[1:5]:", str01[1:5])
    # cut string: start from 1, to last char
    print("str01[1:]:", str01[1:])
    # cut string: start from head(0), end before 5
    print("str01[:5]:", str01[:5])

    # connect string
    str02 = " height 173cm"
    str03 = str01 + str02
    print("info: " + str03)

    # repeat the string multiple times
    print(str01 * 3)

def test_format_string():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

def test_string_array():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    str_list = [
            'string array member 1',
            'string array member 2 xxx',
            'string array member 3 ppppp',
    ]
    for l in str_list:
        print(l)

def test_string_match():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # find sub string
    string = "hello world, hello python"
    if string.find("world") >= 0:
        print("find string \"world\" in string")
    else:
        print("does not find string \"world\" in string")

    # regular match
    if re.search("world.*python", string) != None:
        print("find \"world.*python\" in string")
    else:
        print("does not find \"world.*python\" in string")

def main():
    test_define_string()
    test_format_string()
    test_string_array()
    test_string_match()

if __name__ == '__main__':
    main()
