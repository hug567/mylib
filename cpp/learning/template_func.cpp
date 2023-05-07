// c++ function template
// 2023.05.07

#include <iostream>

using namespace std;

template <typename T>
T const& Max(T const& a, T const& b) {
    return a > b ? a : b;
}

static void testFunctionTemplate(void) {
    // int
    cout << "Max(1, 2) = " << Max(1, 2) << endl;
    // double
    cout << "Max(3.4, 5.6) = " << Max(3.4, 5.6) << endl;
    // string
    cout << "Max(\"abcd\", \"efgh\") = \"" << Max("abcd", "efgh") << "\"" << endl;
}

int main(void)
{
    testFunctionTemplate();
    return 0;
}
