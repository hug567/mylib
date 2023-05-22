// leetcode 2: 两数相加 [中等]
// 2023.05.04

#include <iostream>
#include <vector>
#include <string>
#include "common.h"

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
        int sum, carry = 0, tmp;
        int len1 = length(l1);
        int len2 = length(l2);
        ListNode *shortList, *longList, *ret, *tail, *node;

        longList = len1 > len2 ? l1 : l2;
        shortList = len1 > len2 ? l2 : l1;
        ret = longList;
        while (longList != nullptr) {
            if (shortList != nullptr) {
                tmp = shortList->val;
            } else {
                tmp = 0;
            }
            sum = longList->val + tmp + carry;
            longList->val = sum % 10;
            carry = sum / 10;
            if (longList->next == nullptr) {
                tail = longList;
            }
            longList = longList->next;
            if (shortList != nullptr) {
                shortList = shortList->next;
            }
        }
        if (carry != 0) {
            node = new ListNode;
            node->val = carry;
            node->next = nullptr;
            tail->next = node;
        }

        return ret;
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

    for (i = 0; i < (int)arr.size(); i++) {
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
    class Solution s;

    printList(l1);
    printList(l2);

    ListNode *sum = s.addTwoNumbers(l1, l2);
    printList(sum);
}

void test02(void)
{
    vector<int> arr01 = {0};
    vector<int> arr02 = {0};
    ListNode *l1 = createList(arr01);
    ListNode *l2 = createList(arr02);
    class Solution s;

    printList(l1);
    printList(l2);

    ListNode *sum = s.addTwoNumbers(l1, l2);
    printList(sum);
}

void test03(void)
{
    vector<int> arr01 = {9, 9, 9, 9, 9, 9, 9};
    vector<int> arr02 = {9, 9, 9, 9};
    ListNode *l1 = createList(arr01);
    ListNode *l2 = createList(arr02);
    class Solution s;

    printList(l1);
    printList(l2);

    ListNode *sum = s.addTwoNumbers(l1, l2);
    printList(sum);
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}
