/*
 * C++结构体模板
 * 2021-10-28
 */
#include <iostream>

using namespace std;

// 模板定义结构体数据类型
template <typename T>  //T可为基本数据类型int, float, double等
struct Point {
  T a, b;
  // 结构体构造函数
  Point(T x = 0, T y = 0) :a(x), b(y) {}  //有参数时的构造函数
};

// 加号+重载
template <typename T>
Point<T> operator + (const Point<T> &A, const Point<T> &B) {
  return Point<T>(A.a + B.a, A.b + B.b);
}

// 减号-重载
template <typename T>
Point<T> operator - (const Point<T> &A, const Point<T> &B) {
  return Point<T>(A.a - B.a, A.b - B.b);
}

// 流输出<<重载
template <typename T>
ostream& operator << (ostream &out, const Point<T> &p) {
  out << "(" << p.a << "," << p.b << ")";
  return out;
}

int main(void)
{
  Point<int> a = Point<int>(1, 2);  //定义结构体变量
  Point<int> b(3, 4);  //定义结构体变量
  Point<int> c(0, 0);  //定义结构体变量
  c = a + b;
  cout << "point c: " << c << endl;
  c = a - b;
  cout << "point c: " << c << endl;

  Point<double> d(5.5, 6.5), e(7, 8), f(0.0, 0.0);  //定义结构体变量
  f = d + e;
  cout << "point f: " << f << endl;
  f = d - e;
  cout << "point f: " << f << endl;

  return 0;
}
