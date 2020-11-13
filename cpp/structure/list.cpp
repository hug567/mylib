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

bool comp(int num)
{
	return true;
}

int main(void)
{
	int i;
	list<int> test;  //List容器
	list<int>::iterator testIterator; // 迭代器

	if (test.empty()) {
		cout<<"current list is empty"<<endl;
	}

	test.push_back(1); //从尾部插入
	test.push_back(2);
	//从头部插入(入栈)
	for (i = 0; i < 10; i++) {
		test.push_front(i + 10);
	}

	// 遍历列表
	cout<<"stack: ";
	for (testIterator = test.begin(); testIterator != test.end(); ++testIterator) {
		cout<<*testIterator<<" ";
	}
	cout<<endl;

	// 遍历列表
	cout<<"stack: ";
	for_each(test.begin(), test.end(), PrintElement);
	cout<<endl;

	// 统计元素个数
	cout<<"stack len: "<<count_if(test.begin(), test.end(), comp)<<endl;
	cout<<"stack len(size): "<<test.size()<<endl;

	cout<<"stack top: "<<test.front()<<endl;

	return 0;
}
