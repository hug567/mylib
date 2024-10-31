// C++模板类vector
// 2024-10-31

#include <iostream>
#include <vector>

using namespace std;

#define PrintFunctionLine() \
  cout << "[" << __FUNCTION__ << ":" << __LINE__ << \
  "]:---------------------------------------------" << endl;

// vector作为函数参数，必须是引用&
void PrintVector(vector<int> &vec) {
  // 使用迭代器访问成员
  vector<int>::iterator it;

  cout << "vector: ";
  for (it = vec.begin(); it != vec.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

void TestVectorNumber(void) {
  PrintFunctionLine();

  // 创建int型的vector对象
  vector<int> v_int;
  // 尾部插入数字
  v_int.push_back(1);
  v_int.push_back(2);
  v_int.push_back(3);

  // 使用下标访问成员
  cout << "v_int[0]: " << v_int[0] << endl;
  // vector作为函数参数
  PrintVector(v_int);

  // vector大小: vector.size()
  cout << "vector size: " << v_int.size() << endl;

  // 在指定位置前插入一个元素
  v_int.insert(v_int.begin() + 1, 4);
  PrintVector(v_int);

  // 删除指定位置的元素，下标从0开始
  v_int.erase(v_int.begin() + 2);
  PrintVector(v_int);

  // 清空vector
  v_int.clear();
}

int main(void) {
  TestVectorNumber();
  return 0;
}
