// learning cpp vector
// 2023.04.27

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// vector as function parameter
static void printIntVector(vector<int>& arr)
{
    vector<int>::iterator num;

    // use iterator to traverse vector elements
    cout << "arr: ";
    for (num = arr.begin(); num != arr.end(); num++) {
        cout << *num << " ";
    }
    cout << endl;

#ifdef ACCESS_BY_INDEX
    int i;
    cout << "num: ";
    for (i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
#endif
}

// descending sort, default is ascending
static bool compare(const int &a, const int &b)
{
    return a > b;  // descending
}

static void testIntVector(void)
{
    cout << "[" << __func__ << ":" << __LINE__ << "] -----------------" << endl;

    vector<int> arr01;  // create a zero-size array of int
    cout << "vector arr01 size: " << arr01.size() << endl;
    cout << "vector arr01 max size: " << arr01.max_size() << endl;
    cout << "vector arr01 capacity: " << arr01.capacity() << endl;

    // whether  is empty
    if (arr01.empty()) {
        cout << "arr01 is empty" << endl;
    }

    // insert to tail
    arr01.push_back(0);
    arr01.push_back(1);
    arr01.push_back(2);
    arr01.push_back(3);
    arr01.push_back(4);
    arr01.push_back(5);

    // access elements through index
    cout << "arr01[5]: " << arr01[5] << endl;

    printIntVector(arr01);

    // insert elements at the specified location
    // eg: starting from 0, new member's index is 2
    arr01.insert(arr01.begin() + 2, 6);
    printIntVector(arr01);

    // insert to head
    arr01.insert(arr01.begin(), 7);
    printIntVector(arr01);

    // insert to tail, equal to arr01.push_back()
    arr01.insert(arr01.end(), 8);
    printIntVector(arr01);

    // delete by index
    // eg: starting from 0, delete the element with index 2
    arr01.erase(arr01.begin() + 2);
    printIntVector(arr01);

    // reverse
    reverse(arr01.begin(), arr01.end());
    printIntVector(arr01);

    // ascending sort
    sort(arr01.begin(), arr01.end());
    printIntVector(arr01);

    // descending sort
    sort(arr01.begin(), arr01.end(), compare);
    printIntVector(arr01);

    // clear vector
    arr01.clear();
}

// vector as function return value
static vector<int> createIntVector(int x)
{
    int i;
    vector<int> arr;

    for (i = 0; i < x; i++) {
        arr.push_back(i);
    }

    return arr;
}

// vector reference as function return value, has higher efficiency
static void fillIntVector(int x, vector<int> &arr)
{
    int i;

    for (i = 0; i < x; i++) {
        arr.push_back(i);
    }
}

static void testVectorWithFunction(void)
{
    cout << "[" << __func__ << ":" << __LINE__ << "] -----------------" << endl;
    // vector as function return value
    vector<int> arr02 = createIntVector(10);
    printIntVector(arr02);
    arr02.clear();

    vector<int> arr03;
    fillIntVector(8, arr03);
    printIntVector(arr03);
    arr03.clear();
}

int main()
{
    testIntVector();
    testVectorWithFunction();
    return 0;
}