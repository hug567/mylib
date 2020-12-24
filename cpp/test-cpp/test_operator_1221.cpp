/*
 * 练习：运算符重载
 * 时间：2020-12-21
 */
#include <iostream>

using namespace std;

class CBook
{
private:
    int pages;
public:
    CBook();
    ~CBook();
    void setPages(int pages);
    int getPages(void);
    void printPages(void);
    /* 重载运算符 */
    CBook operator+ (CBook b)
    {
        int pages = b.getPages();
        pages += this->pages;
        b.setPages(pages);
        return b;
    }
    CBook operator- (CBook b)
    {
        int pages = b.getPages();
        pages = this->pages - pages;
        b.setPages(pages);
        return b;
    }
};

CBook::CBook()
{
    pages = 0;
}

CBook::~CBook()
{
    pages = 0;
}

void CBook::setPages(int pages)
{
    this->pages = pages;
}

int CBook::getPages(void)
{
    return pages;
}

void CBook::printPages(void)
{
    cout << "pages = " << pages << endl;
}

int main(void)
{
    CBook a, b;
    a.setPages(10);
    a.printPages();
    b.setPages(20);
    b.printPages();

    /* 使用重载的运算符 */
    a = a + b;
    a.printPages(); /* pages = 30 */

    /* 使用重载的运算符 */
    a = a - b;
    a.printPages(); /* pages = 10 */

    return 0;
}
