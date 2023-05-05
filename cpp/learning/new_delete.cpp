// practice: cpp new and delete operator
// 2023.05.05
#include <iostream>

using namespace std;

static void testNewInt(void)
{
    // create int val
    int *num = new int;
    *num = 10;
    cout << "num: " << *num << endl;
    delete num;

    // create int array
    int *arr = new int [10];
    for (int i = 0; i < 10; i++) {
        arr[i] = 10 - i;
    }
    cout << "arr: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    delete [] arr;
}

int main(void)
{
    testNewInt();
    return 0;
}