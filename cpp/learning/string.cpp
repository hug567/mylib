// 练习：string类
// g++ -std=c++11 string.cpp
#include <iostream>

using std::cout;
using std::wcout;
using std::endl;
using std::string;

//c类型的字符串
void string_like_c(void)
{
    cout << "[" << __func__ << ":" << __LINE__ << "]: ----------------" << endl;
    const char *str1 = "c string 1";
    cout << "str1: " << str1 << endl;

    char str2[] = "c string 2";
    cout << "str2: " << str2 << endl;
}

//string类
void string_class(void)
{
    cout << "[" << __func__ << ":" << __LINE__ << "]: ----------------" << endl;
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
    cout << "str6 size: " << str6.size() << endl;
    cout << "str6 len: " << str6.length() << endl;

    // initialize another string using a single element of one string
    string str7 = "012345";
    string str8 = str7.substr(2, 1);
    cout << "str7: " << str7 << ", str8: " << str8 << endl;
}

//其他类似的字符串
static void string_others(void)
{
    cout << "[" << __func__ << ":" << __LINE__ << "]: ----------------" << endl;
    //2字节宽度的字符
    wchar_t str1[] = L"w_char string";
    wcout << "str1: " << str1 << endl;

    //2字节宽度的字符
    char16_t str2[] = u"char16_t string";
    //4字节宽度的字符
    char32_t str3[] = U"char32_t string";

    //原始(raw)字符串
    cout << R"(This is a "raw" string)" << endl;
}

static void testStringCut(void)
{
    cout << "[" << __func__ << ":" << __LINE__ << "]: ----------------" << endl;
    string str = "0123456789";

    // get the substring from index 2 to the end
    string sub = str.substr(2);
    cout << "sub string: " << sub << endl;

    // get the substring from index 2 with length 3
    sub = str.substr(2, 3);
    cout << "sub string: " << sub << endl;
}

int main(void)
{
    string_like_c();
    string_class();
    string_others();
    testStringCut();

    return 0;
}
