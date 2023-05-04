// leetcode 2: 两数相加 [中等]
// 2023.05.04

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/***** submit code ************************************************************/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int len1 = length(l1);
        int len2 = length(l2);
        int retLen = len1 > len2 ? len1 : len2;
        ListNode *ret = nullptr, *tmp = nullptr;

        if (len1 > len2) {
            ret = l1;
        } else {
            ret = l2;
        }

        return nullptr;
    }
private:
    int length(const ListNode *l);
};

int Solution::length(const ListNode *l)
{
    int len = 0;

    while (l != nullptr) {
        len++;
        l = l->next;
    }

    return len;
}

/***** local debug ************************************************************/
struct ListNode *createList(const vector<int> & arr)
{
    int i;
    struct ListNode *head, *tail, *tmp;

    for (i = 0; i < arr.size(); i++) {
        tmp = new ListNode;
        tmp->val = arr[i];
        tmp->next = nullptr;
        if (i == 0) {
            head = tmp;
            tail = tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
    }

    return head;
}

void printList(const struct ListNode *l)
{
    cout << "list: ";
    while (l != nullptr) {
        cout << l->val << " ";
        l = l->next;
    }
    cout << endl;
}

void test01(void)
{
    vector<int> arr01 = {2, 4, 3};
    vector<int> arr02 = {5, 6, 4};
    ListNode *l1 = createList(arr01);
    ListNode *l2 = createList(arr02);

    printList(l1);
    printList(l2);
}

int main()
{
    test01();
    return 0;
}