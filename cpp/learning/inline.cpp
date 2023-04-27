// c++ inline function
// 2023.04.27

#include <iostream>

using namespace std;

static inline int add(int a, int b)
{
    return a + b;
}

static void test_inline(void)
{
    cout << "1 + 2 = " << add(1, 2) << endl;
}

int main()
{
    test_inline();
    return 0;
}