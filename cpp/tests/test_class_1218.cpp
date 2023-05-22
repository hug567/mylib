#include <iostream>

using namespace std;

#define MAX_NAME_SIZE 20

/* 声明类 */
class CStudent 
{
private:
    char name[MAX_NAME_SIZE];
    int age;
public:
    /*构造函数*/
    CStudent(void);
    CStudent(const char *name);
    CStudent(int age);
    CStudent(const char *name, int age);
    /* 复制构造函数 */
    CStudent(CStudent &stu);
    /* 对外接口 */
    void printInfo(void);
    void setName(const char *name);
    char *getName(void);
    void setAge(int age);
    int getAge(void);
};

/* 构造函数 */
CStudent::CStudent()
{
    memset(this->name, 0, MAX_NAME_SIZE);
    this->age = 0;
}

CStudent::CStudent(const char *name)
{
    this->setName(name);
    this->age = 0;
}

CStudent::CStudent(int age)
{
    memset(this->name, 0, MAX_NAME_SIZE);
    this->setAge(age);
}

CStudent::CStudent(const char *name, int age)
{
    this->setName(name);
    this->setAge(age);
}

/* 复制构造函数 */
CStudent::CStudent(CStudent &stu)
{
    memset(this->name, 0, MAX_NAME_SIZE);
    strcpy(this->name, stu.name);
    this->age = stu.age;
}

/* 对外接口 */
void CStudent::printInfo(void)
{
    cout << "name: " << this->name << endl;
    cout << "age: " << this->age << endl;
}

void CStudent::setName(const char *name)
{
    if (strlen(name) > MAX_NAME_SIZE) {
        cout << name << "is too long" << endl;
        return;
    }
    memset(this->name, 0, MAX_NAME_SIZE);
    strcpy(this->name, name);
}

char *CStudent::getName(void)
{
    return this->name;
}

void CStudent::setAge(int age)
{
    this->age = age;
}

int CStudent::getAge(void)
{
    return this->age;
}

int main(void)
{
    /* 声明对象 */
    CStudent stu1("zhangsan", 18);
    stu1.printInfo();
    cout << "name: " << stu1.getName() << ", age: " << stu1.getAge() << endl;
    stu1.setName("lisi");
    stu1.printInfo();
    stu1.setAge(20);
    stu1.printInfo();

    CStudent stu2;
    stu2.printInfo();
    stu2.setName("wangwu");
    stu2.printInfo();
    stu2.setAge(22);
    stu2.printInfo();

    /* 复制构造函数初始化对象 */
    cout << "[INFO ] copy constructor init object:"  << endl;
    CStudent stu3(stu2);
    stu3.printInfo();

    return 0;
}
