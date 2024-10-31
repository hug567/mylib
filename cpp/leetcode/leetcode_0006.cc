// leetcode 6: Z字形变换 [中等]
// 2024-10-31

#include <iostream>

using namespace std;

// 提交代码: -------------------------------------------------------------------
class Solution {
public:
    string convert(string s, int numRows) {
        return s;
    }
};

// 本地测试: -------------------------------------------------------------------
void Test01(void) {
    cout << __func__ << ": -------------------------------------------" << endl;

    string s = "PAYPALISHIRING";
    int numRows = 3;
    Solution sol;
    string convert = sol.convert(s, numRows);
    cout << "convert:(PAHNAPLSIIGYIR) " << convert << endl;
}

void Test02(void) {
    cout << __func__ << ": -------------------------------------------" << endl;

    string s = "PAYPALISHIRING";
    int numRows = 4;
    Solution sol;
    string convert = sol.convert(s, numRows);
    cout << "convert:(PINALSIGYAHRPI) " << convert << endl;
}

void Test03(void) {
    cout << __func__ << ": -------------------------------------------" << endl;

    string s = "A";
    int numRows = 1;
    Solution sol;
    string convert = sol.convert(s, numRows);
    cout << "convert:(A) " << convert << endl;
}

int main(void) {
    Test01();
    return 0;
}
