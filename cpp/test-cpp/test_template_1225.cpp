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

int main(void)
{
    /* 使用模板函数 */
    cout << "Sum(10, 20) = " << Sum(10, 20) << endl;
    cout << "Sum(10.0, 20.0) = " << Sum(10.0, 20.0) << endl;
    cout << "Sum<int>(10.5, 20) = " << Sum<int>(10.5, 20) << endl;
    cout << "Sum<double>(10.5, 20) = " << Sum<double>(10.5, 20) << endl;
    return 0;
}
