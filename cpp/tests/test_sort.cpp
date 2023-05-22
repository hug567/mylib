/*
 * 练习：sort排序函数
 * 2021-03-26
 */

#include <iostream>
#include <vector>
#include <random>

using namespace std;

void PrintArray(vector<int>&arr)
{
	vector<int>::iterator n = arr.begin(); //容器成员

	cout << "array: ";
	while (n < arr.end()) { //遍历
		cout << *n << " "; //取值
		n++;
	}
	cout << endl;
}

void TestArray(void)
{
	int i;
	vector<int>arr; //整形容器数组

	for (i = 0; i < 10; i++) {
		arr.push_back(i); //向尾部追加整形值
	}

	PrintArray(arr); //整形容器数组做函数参数

	cout << "first: " << *arr.begin() << endl; //第一个元素
	cout << "first: " << arr.front() << endl; //第一个元素
	cout << "end: " << *(arr.end() - 1) << endl; //最后一个元素
	cout << "end: " << arr.back() << endl; //最后一个元素

	//尾部插入元素
	arr.push_back(10);
	PrintArray(arr);

	//删除尾部元素
	arr.pop_back();
	PrintArray(arr);

	//元素个数
	cout << "size: " << arr.size() << endl;
	//可用空间大小
	cout << "capacity: " << arr.capacity() << endl;

	//是否为空
	cout << "empty: " << arr.empty() << endl;

	//读取第5个元素
	cout << "index 5: " << arr.at(5) << endl;

	//清空容器
	arr.clear();
	cout << "empty: " << arr.empty() << endl;
}

int main(void)
{
	TestArray();
	return 0;
}
