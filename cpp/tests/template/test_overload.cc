// C++重载模板
// 2024-10-30

#include <iostream>

using namespace std;

#define PrintFunctionLine() \
  cout << "[" << __FUNCTION__ << ":" << __LINE__ << \
  "]:---------------------------------------------" << endl;

// 定义函数模板
template <typename T>
void Swap(T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

// 重载函数模板，参数类型及参数数量不同
template <typename T>
void Swap(T *a, T *b, int n) {
  T temp;

  for (int i = 0; i < n; i++) {
    temp = a[i];
    a[i] = b[i];
    b[i] = temp;
  }
}

void TestOverload(void){
  PrintFunctionLine();

  int int_a = 2;
  int int_b = 5;
  Swap(int_a, int_b);
  cout << "a = " << int_a << ", b = " << int_b << endl;

  float float_a[] = {1, 2, 3};
  float float_b[] = {6, 5, 4};
  Swap(float_a, float_b, 3);
  cout << "float_a: ";
  for (int i = 0; i < 3; i++) {
    cout << float_a[i] << " ";
  }
  cout << endl;
  cout << "float_b: ";
  for (int i = 0; i < 3; i++) {
    cout << float_b[i] << " ";
  }
  cout << endl;
}

int main(void)
{
  TestOverload();

  return 0;
}
