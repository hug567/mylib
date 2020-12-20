#include <iostream>

class CNode
{
private:
    int val;
    class CNode *next;
public:
    CNode createNode(int val);
    int getVal(void);
};

class CList
{
private:
    CNode head;
public:
    void init(void);
};

using namespace std;

int main(void)
{
    return 0;
}