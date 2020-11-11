/* leetcode 138: 复制带随机指针的链表(中等) */
#include <iostream>
using namespace std;

class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node() {}

	Node(int _val, Node* _next, Node* _random) {
		val = _val;
		next = _next;
		random = _random;
	}
};

class Solution {
public:
	Node* copyRandomList(Node* head) {

	}
};

int main()
{
	cout << "hello first cpp" << endl;
	return 0;
}
