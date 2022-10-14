// 练习：string类
// g++ -std=c++11 string.cpp
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void string_usage(void)
{
    // string拼接
    string str1 = "test string 1";
    cout << "str1: " << str1 << endl;
    cout << "str1 length: " << str1.length() << endl;
    cout << "str1 first char: " << str1[0] << endl;
    cout << "str1 sixth char: " << str1[5] << endl;

    string str2 = {"test string 2"};
    cout << "str2: " << str2 << endl;

    // string拼接
    string str3 = str1 + str2;
    cout << "str3: " << str3 << endl;
}

int main(void)
{
    string_usage();
    return 0;
}
