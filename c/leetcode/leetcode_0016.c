/*
 * leetcode 16: 最接近的三数之和 [中等]
 * 思路：排序 + 双指针
 *   1)、对数组排序后，第1个指针从0遍历到n-2；
 *   2)、第1个指针固定后，第2、3个指针分别指向剩余数组的头尾，分别向中间移动；
 *   3)、移动方式为：若 *p1 + *p2 + *p3 >= target，p3向左移动，减小三个数的和；
 *                 若 *p1 + *p2 + *p3 < target，p3向右移动，增大三个数的和；
 *   4)、若有：*p1 + *p2 + *p3 == target, 直接返回0；
 *   5)、p2、p3移动过程中，可移动至下一个不同的值；
 *   6)、注意最短距离初始值的选择；
 * 2022-03-07
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int threeSumClosest(int* nums, int numsSize, int target)
{
    int i;
    int tmp, closest;
    int *p1, *p2, *p3;

    qsort(nums, numsSize, sizeof(int), Compare);
    closest = 1e7;
    for (i = 0; i < numsSize - 2; i++) {
        p1 = nums + i;
        p2 = p1 + 1;
        p3 = nums + numsSize - 1;
        while (p2 < p3) {
            tmp = *p1 + *p2 + *p3;
            if (tmp == target) {
                return target;
            } else if (tmp >= target) {
                while (p3 > p2 && *p3 == *(p3 - 1)) {
                    p3--;
                }
                p3--;
            } else {
                while (p2 < p3 && *p2 == *(p2 + 1)) {
                    p2++;
                }
                p2++;
            }
            closest = abs(closest - target) < abs(tmp - target) ? closest : tmp;
         }
    }

    return closest;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int nums[] = { -1, 2, 1, -4 };
    int size = ARRAY_SIZE(nums);
    int target = 1;
    Log("closest: %d(2)\n", threeSumClosest(nums, size, target));
}

void TestCase2(void)
{
    int nums[] = { 0, 0, 0 };
    int size = ARRAY_SIZE(nums);
    int target = 1;
    Log("closest: %d(0)\n", threeSumClosest(nums, size, target));
}

void TestCase3(void)
{
    int nums[] = { -111,-111,3,6,7,16,17,18,19 };
    int size = ARRAY_SIZE(nums);
    int target = 13;
    Log("closest: %d(16)\n", threeSumClosest(nums, size, target));
}

void TestCase4(void)
{
    int nums[] = {
            47,-48,-72,97,-78,50,-22,18,9,24,28,-53,44,-96,50,45,86,11,21,-44,
            67,83,55,-86,-33,0,-53,-94,-60,57,-72,-73,-27,13,91,80,18,-80,-29,
            -69,-74,-90,54,22,3,91,-47,-32,80,-55,69,-95,62,-92,4,-86,62,3,23,
            -30,-4,0,49,24,10,-32,79,-99,-66,-30,-83,-13,90,-27,9,-4,9,98,-70,
            -19,32,24,-77,83,11,-78,-94,4,41,61,20,96,-36,54,-46,-51,91,54,30,
            -42,82,0,9,24,-2,32,-16,-18,87,23,78,-10,-82,-67,68,-18,-61,91,-90,
            -53,67,-48,12,1,-71,-99,31,82,39,-56,23,-89,-58,19,-60,39,-23,-76,
            -85,67,-33,69,-74,-8,-99,52,-70,-71,85,-8,28,-3,-100,18,88,5,-16,
            17,91,-35,22,-76
    };
    int size = ARRAY_SIZE(nums);
    int target = 298;
    Log("closest: %d(291)\n", threeSumClosest(nums, size, target));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}
