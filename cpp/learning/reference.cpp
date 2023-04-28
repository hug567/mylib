// learning cpp reference
// 2023.04.28

#include <iostream>

using namespace std;

static void testVariableReference(void)
{
    int num;
    int & ref = num;  // must be initialized when defining a reference

    num = 10;
    cout << "ref = " << ref << endl;

    ref += 5;
    cout << "num = " << num << endl;

    // num and ref point to the same memory
    cout << "num addr: " << &num << endl;
    cout << "ref addr: " << &ref << endl;
}

static void increaseInt(int & num)
{
    num++;
}

// const reference, can not change variable value in function
static void constReference(int & num)
{
    cout << "const ref num: " << num << endl;
}

// array reference as function parameter
// recommended use of vector
static void printArrayReference(int (&arr)[5])
{
    int i;
    int size = sizeof(arr) / sizeof(int);

    cout << "arr: ";
    for (i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

static void testFunctionParameterReference(void)
{
    int x = 5;

    // only variable can be passed, cannot contain any constants
    // eg: increaseInt(x + 5) is illegal
    increaseInt(x);
    cout << "x = " << x << endl;

    // const reference as function parameter
    constReference(x);

    int arr[] = { 1, 2, 3, 4, 5 };
    printArrayReference(arr);
}

struct Studend {
    char name[30];
    int score;
};

static void addStudendScore(struct Studend &stu)
{
    stu.score += 5;
}

static void testStructReference(void)
{
    struct Studend bob = { "Bob", 80 };

    cout << bob.name << " score: " << bob.score << endl;
    addStudendScore(bob);
    cout << bob.name << " score: " << bob.score << endl;
}

int main()
{
    testVariableReference();
    testFunctionParameterReference();
    testStructReference();
    return 0;
}