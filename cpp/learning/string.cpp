// 练习：string类
// g++ -std=c++11 string.cpp
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void string_usage(void)
{
    // string定义
    string str1 = "test string 1";
    cout << "str1: " << str1 << endl;
    cout << "str1 length: " << str1.length() << endl;
    cout << "str1 first char: " << str1[0] << endl;
    cout << "str1 sixth char: " << str1[5] << endl;

    // string初始化
    string str2 = {"test string 2"};
    cout << "str2: " << str2 << endl;

    // string拼接
    string str3 = str1 + ", " + str2;
    cout << "str3: " << str3 << endl;

    // string赋值
    string str4 = str3;
    cout << "str4: " << str4 << endl;
    string str5 = "str5, ";
    str5 += str1;
    cout << "str5: " << str5 << endl;
    string str6;
    str6 += "str6";
    cout << "str6: " << str6 << endl;

    // string长度
    cout << "str6 len: " << str6.size() << endl;
    cout << "str6 len: " << str6.length() << endl;
}

int main(void)
{
    string_usage();
    return 0;
}
