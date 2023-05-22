// 2023-05-22
#include <iostream>
#include <iostream>

using namespace std;

static void test_string_find(void)
{
    // find sub string
    string all = "1234567890";
    string sub = "456";
    if (all.find(sub) != std::string::npos) {
        cout << "find [" << sub << "] in string: [" << all << "]" << endl;
    }
}

int main(void)
{
    test_string_find();

    return 0;
}
