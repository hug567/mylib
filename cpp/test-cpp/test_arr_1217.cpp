#include <iostream>

using namespace std;

/* 结构体定义 */
struct Student {
    char name[20];
    int age;
};

/* 通过引用传递参数，类似制作，将修改实参的值 */
void Add(int &num, int val)
{
    num += val;
}

/* 结构体变量声明方式，引用作函数参数 */
void PrintStudentInfo(Student &stu)
{
    cout << "name: " << stu.name << endl;
    cout << "age: " << stu.age << endl;
}

int main(void)
{
    int a = 0;
    cout << "a = " << a << endl;
    Add(a, 2);
    cout << "a = " << a << endl;

    /* 结构体变量声明、初始化方式 */
    Student stu = { "zhangsan", 18 };
    /* 给参数为引用的函数传递变量 */
    PrintStudentInfo(stu);

    return 0;
}
