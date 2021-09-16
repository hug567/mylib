/*
 * leetcode 9: 回文数 [简单]
 * 2021-09-16
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
bool isPalindrome(int x){
    int i;
    int count  = 0;
    char num[10] = {0};

    if (x < 0) {
        return false;
    } else if (x < 10) {
        return true;
    }
    while (x > 0) {
        num[count] = x % 10;
        x /= 10;
        count++;
    }
    for (i = 0; i < count / 2; i++) {
        if (num[i] != num[count - i - 1]) {
            return false;
        }
    }
    return true;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    DebugLog("isPalindrome(121) = %d\n", isPalindrome(121));
    DebugLog("isPalindrome(-121) = %d\n", isPalindrome(-121));
    DebugLog("isPalindrome(10) = %d\n", isPalindrome(10));
    DebugLog("isPalindrome(-101) = %d\n", isPalindrome(-101));
    DebugLog("isPalindrome(1234321) = %d\n", isPalindrome(1234321));
    DebugLog("isPalindrome(1234567) = %d\n", isPalindrome(1234567));
    DebugLog("isPalindrome(2147483647) = %d\n", isPalindrome(2147483647));
    DebugLog("isPalindrome(-2147483648) = %d\n", isPalindrome(-2147483648));

    return 0;
}
