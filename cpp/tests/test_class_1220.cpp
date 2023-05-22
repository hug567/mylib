/*
 * 学习类的继承和派生
 * 2020-12-20
 */
#include <iostream>

using namespace std;

const int MAX_NAME_SIZE = 20;

class CPersion
{
protected:  /* 可被子类访问 */
    char name[MAX_NAME_SIZE];
    int age;
public:
    CPersion(); /* 构造析构函数一般声明为public */
    ~CPersion(); /* 析构函数 */
    void setName(const char *name);
    void setAge(int age);
    char *getName(void);
    int getAge(void);
    void printInfo(void);
};

/* 公有继承父类 */
class CStudent : public CPersion
{
private:
    int _class;
public:
    CStudent(); /* 构造函数 */
    ~CStudent(); /* 析构函数 */
    void setClass(int _class);
    int getClass(void);
    void printInfo(void); /* 子类重载父类方法 */
};

/* 构造函数 */
CPersion::CPersion()
{
    memset(name, 0, MAX_NAME_SIZE);
    age = 0;
}

/* 析构函数 */
CPersion::~CPersion()
{}

void CPersion::setName(const char *name)
{
    if (name == NULL || strlen(name) > MAX_NAME_SIZE - 1) {
        cout << "name is NULL or too long" << endl;
        return;
    }
    memset(this->name, 0, MAX_NAME_SIZE);
    strcpy(this->name, name);
}

char *CPersion::getName(void)
{
    return name;
}

void CPersion::setAge(int age)
{
    this->age = age;
}

int CPersion::getAge(void)
{
    return age;
}

void CPersion::printInfo(void)
{
    cout << "persion info:" << endl;
    cout << "name: " << name << endl; 
    cout << "age: " << age << endl; 
}

/* 子类构造函数，创建对象时默认先调用父类无参构造函数 */
CStudent::CStudent()
{
    _class = 0;
}

/* 析构函数 */
CStudent::~CStudent()
{}

void CStudent::setClass(int _class)
{
    this->_class = _class;
}

int CStudent::getClass(void)
{
    return _class;
}

void CStudent::printInfo(void)
{
    CPersion::printInfo(); /* 子类调用父类同名方法 */
    cout << "class: " << _class << endl;
}

int main(void)
{
    CStudent stu1;
    stu1.setName("xi xi");
    stu1.setAge(18);
    stu1.setClass(6);
    stu1.printInfo();

    /* 子类对象调用父类中的方法 */
    stu1.CPersion::printInfo();

    return 0;
}
