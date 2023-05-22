// leetcode 5: 最长回文子串 [中等]
// 2023.05.05

#include <iostream>
#include <string>
#include "common.h"

using namespace std;

#define LOCAL_SOLUTION_01

/***** submit code ************************************************************/
// 方案一：
// 思路：回文串的中心可以是1个或2个字符，以回文串中心为起点，向两边扩展，查找
//       最长回文子串
#ifdef LOCAL_SOLUTION_01
class Solution {
public:
    void palindromeCenterOneChar(const string & s, int center, string & pal) {
        int l = center, r = center;
        pal = s.substr(center, 1);

        while (l >=0 && r < (int)s.length()) {
            if (s[l] == s[r]) {
                pal = s.substr(l, r - l + 1);
                l--;
                r++;
            } else {
                break;
            }
        }
    }

    void palindromeCenterTwoChar(const string & s, int start, string & pal) {
        int l = start, r = start + 1;

        if (r >= (int)s.length() || s[l] != s[r]) {
            pal = "";
            return;
        }

        pal = s.substr(start, 2);
        while (l >=0 && r < (int)s.length()) {
            if (s[l] == s[r]) {
                pal = s.substr(l, r - l + 1);
                l--;
                r++;
            } else {
                break;
            }
        }
    }

    string longestPalindrome(string s) {
        string sub = "", tmp;
        int len = s.length();

        // TODO: Where acceleration can be optimized
        //for (int i = 0; i < len && (sub.length() < (len - i)); i++) {
        for (int i = 0; i < len; i++) {
            palindromeCenterOneChar(s, i, tmp);
            if (sub.length() < tmp.length()) {
                sub = tmp;
            }
            palindromeCenterTwoChar(s, i, tmp);
            if (sub.length() < tmp.length()) {
                sub = tmp;
            }
        }
        s = sub;
        return s;
    }
};
#endif

#ifdef LOCAL_SOLUTION_02
class Solution {
public:
    string longestPalindrome(string s) {
        return s;
    }
};
#endif

/***** local debug ************************************************************/
static void test01(void)
{
    string s = "babad";
    class Solution sol;
    cout << "origin str: " << s << ", ";
    cout << "sub str: " << sol.longestPalindrome(s) << endl;
}

static void test02(void)
{
    string s = "cbbd";
    class Solution sol;
    cout << "origin str: " << s << ", ";
    cout << "sub str: " << sol.longestPalindrome(s) << endl;
}

static void test03(void)
{
    string s = "ccc";
    class Solution sol;
    cout << "origin str: " << s << ", ";
    cout << "sub str: " << sol.longestPalindrome(s) << endl;
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}
