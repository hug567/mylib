/*
 * 练习：C++模板
 * 2020-12-25
 */
#include <iostream>

using namespace std;

/* 模板类型 */
template <class type>
/* 模板函数 */
type Sum(type a, type b)
{
    return a + b;
}

/* 函数模板 */
template <class type>
type Min(type a, type b)
{
    if (a < b) {
        return a;
    } else {
        return b;
    }
}
/* 重载函数模板 */
char *Min(char *a, char *b)
{
    if (strcmp(a, b)) {
        return b;
    } else {
        return a;
    }
}

int main(void)
{
    /* 使用模板函数 */
    cout << "Sum(10, 20) = " << Sum(10, 20) << endl;
    cout << "Sum(10.0, 20.0) = " << Sum(10.0, 20.0) << endl;
    cout << "Sum<int>(10.5, 20) = " << Sum<int>(10.5, 20) << endl;
    cout << "Sum<double>(10.5, 20) = " << Sum<double>(10.5, 20) << endl;

    /* 使用重载函数模板 */
    cout << "Min(3, 4) = " << Min(3, 4) << endl;
    cout << "Min(6.0, 5.0) = " << Min(6.0, 5.0) << endl;
    cout << "Min(""huang"", ""xing"") = " << Min("huang", "xing") << endl;

    return 0;
}
