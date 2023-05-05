// leetcode 3: 无重复字符的最长子串 [中等]
// 思路：滑动窗口, 若[l,r]范围内无重复字符，则[l+1,r]范围内也无重复字符
// 2023.05.05
#include <iostream>
#include <string>

using namespace std;

/***** submit code ************************************************************/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max = 0;
        int len = s.length();
        int l = 0, r = 0, flag = 0;

        if (len <= 1) {
            return len;
        }
        while (l < len && r < len) {
            max = max > r - l + 1 ? max : r - l + 1;
            if (r + 1 == len) {
                break;
            }
            for (int i = l; i < r + 1; i++) {
                if (s[i] == s[r + 1]) {
                    l++;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                r++;
            }
            flag = 0;
        }
        return max;
    }
};

/***** local debug ************************************************************/
static void test01(void)
{
    string s = "abcabcbb";
    class Solution sol;
    cout << "sub len(3): " << sol.lengthOfLongestSubstring(s) << endl;
}

static void test02(void)
{
    string s = "bbbbb";
    class Solution sol;
    cout << "sub len(1): " << sol.lengthOfLongestSubstring(s) << endl;
}

static void test03(void)
{
    string s = "pwwkew";
    class Solution sol;
    cout << "sub len(3): " << sol.lengthOfLongestSubstring(s) << endl;
}

static void test04(void)
{
    string s = "";
    class Solution sol;
    cout << "sub len(0): " << sol.lengthOfLongestSubstring(s) << endl;
}

int main()
{
    test01();
    test02();
    test03();
    test04();
    return 0;
}