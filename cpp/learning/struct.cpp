// practice: c++ struct
// 2023.05.04

#include <iostream>

using namespace std;

struct Student {
    string name;
    int age;

    // struct constructor
    Student();
    // implement the constructor inside the structure
    Student(string name, int age): name(name), age(age) {};

    // struct normal function
    void showInfo(void);
};

// implement the constructor outside the structure
Student::Student()
{
    this->name = "";
    this->age = 0;
}

void Student::showInfo(void)
{
    cout << "student name: " << this->name << ", age: " << this->age << endl;
}

static void testUsingStructConstructor(void)
{
    struct Student s1;
    s1.showInfo();
    s1.name = "alice";
    s1.age = 15;
    s1.showInfo();

    struct Student s2("bob", 18);
    s2.showInfo();
}

int main()
{
    testUsingStructConstructor();
    return 0;
}