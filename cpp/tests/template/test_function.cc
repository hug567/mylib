// C++函数模板
// 2024-10-30

#include <iostream>

using namespace std;

//----------------------------------------------------------------------------//
// 定义函数模板
template <typename T>
T Add(T &a, T &b)
{
  return a + b;
}

// 结构体
struct Point {
  int x;
  int y;

  // 结构体重载运算符: +
  Point operator+ (const Point &b) {
    struct Point temp;
    temp.x = this->x + b.x;
    temp.y = this->y + b.y;
    return temp;
  }

  // 结构体重载输出流: <<
  friend ostream& operator<< (ostream&, Point &p) {
    cout << "(" << p.x << ", " << p.y << ")";
    return cout;
  }
};

//----------------------------------------------------------------------------//
// 基本类型数据使用函数模板
void TestFunction(void) {
  cout << "[" << __FUNCTION__ << ":" << __LINE__ <<
    "]:---------------------------------------------" << endl;

  //使用模板
  int int_a = 2;
  int int_b = 3;
  int sum_int = Add(int_a, int_b);
  cout << "sum_int = " << sum_int << endl;

  //使用模板
  int float_a = 5.0f;
  int float_b = 7.0f;
  int sum_float = Add(float_a, float_b);
  cout << "sum_float = " << sum_float << endl;
}

// 结构体类型使用函数模板
void TestStruct(void) {
  cout << "[" << __FUNCTION__ << ":" << __LINE__ <<
    "]:---------------------------------------------" << endl;

  struct Point point_a = {1, 2};
  struct Point point_b = {1, 4};
  // 结构体使用模板函数，需先重载模板中对成员使用的操作符，如：+
  struct Point point_sum = Add(point_a, point_b);
  cout << "point_sum: " << point_sum << endl;
}

int main(void) {
  TestFunction();
  TestStruct();
  return 0;
}
