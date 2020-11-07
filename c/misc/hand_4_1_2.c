/*
 * 《手写代码必备手册》 4.1.2 汉诺塔问题
 * 最少此处：2^n - 1 (即：(1 << n) - 1)
 * 2020-11-04
 */
#include <stdio.h>
/*
void hanoi(int n, char x, char y, char z)
{
    if (n == 1) {
        return;
    }
}
*/

int main(void)
{
    unsigned int n = 4;
    printf("count = %d\n", (1 << n) - 1);
    return 0;
}