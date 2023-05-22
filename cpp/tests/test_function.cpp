// learning cpp function
// 2023-05-22

#include <iostream>
#include <stdarg.h> /* 可变参数 */

using namespace std;

/* 函数带默认参数 */
int Add(int a = 1, int b = 2)
{
    return a + b;
}

/* 函数具有可变参数 */
void Print(int num, ...)
{
    va_list args;
    va_start(args, num);
    while (num--) {
        char *str = va_arg(args, char *);
        cout << str <<endl;
    }
    va_end(args);
}

/* 重载函数：通过函数参数区分同名函数 */
double Add(double a, double b)
{
    return a + b;
}

/* 内联函数：编译后无符号 */
inline int Dec(int a, int b)
{
    return a - b;
}

/* 静态局部变量：函数调用结束后值不消失 */
void PrintLocalStaticVar(void)
{
    static int count = 0;
    count++;
    cout << "local count = " << count << endl;
}

int main(void)
{
    cout << "With default var, Add() = " << Add() << endl;
    cout << "Add(3, 4) = " << Add(3, 4) << endl;
    Print(4, "Name:", "huangxing", "Age:", "28");
    cout << "Add(5.0, 6.0) = " << Add(5.0, 6.0) << endl;
    cout << "Dec(8, 7) = " << Dec(8, 7) << endl;
    PrintLocalStaticVar();
    PrintLocalStaticVar();
    PrintLocalStaticVar();
    return 0;
}
