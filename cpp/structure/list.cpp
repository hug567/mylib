/* 单链表 */
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintElement(int ele)
{
	cout<<ele<<" ";
}

int main(void)
{
	list<int> test;  //List容器
	list<int>::iterator testIterator; // 迭代器

	if (test.empty()) {
		cout<<"current list is empty"<<endl;
	}

	test.push_back(1); //从尾部插入
	test.push_back(2);
	test.push_front(3); //从头部插入(入栈)
	test.push_front(4);

	// 遍历列表
	cout<<"list: ";
	for (testIterator = test.begin(); testIterator != test.end(); ++testIterator) {
		cout<<*testIterator<<" ";
	}
	cout<<endl;

	// 遍历列表
	cout<<"list: ";
	for_each(test.begin(), test.end(), PrintElement);
	cout<<endl;

	return 0;
}
