// 两数之和 [简单]
// 2023.04.27

#include <iostream>
#include <vector>

using namespace std;

/***** submit code ************************************************************/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i, j;
        vector<int> ret;

        for (i = 0; i < (int)nums.size() - 1; i++) {
            for (j = i + 1; j < (int)nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    ret.push_back(i);
                    ret.push_back(j);
                    return ret;
                }
            }
        }
        return ret;
    }
};

/***** local debug ************************************************************/
void test01(void)
{
    vector<int> num = {2, 7, 11, 15};
    int target = 9;
    class Solution solu;
    vector<int> ret;

    ret = solu.twoSum(num, target);
    cout << "[" << ret[0] << "," << ret[1] << "]" << endl;
}

void test02(void)
{
    vector<int> num = {3, 2, 4};
    int target = 6;
    class Solution solu;
    vector<int> ret;

    ret = solu.twoSum(num, target);
    cout << "[" << ret[0] << "," << ret[1] << "]" << endl;
}

void test03(void)
{
    vector<int> num = {3, 3};
    int target = 6;
    class Solution solu;
    vector<int> ret;

    ret = solu.twoSum(num, target);
    cout << "[" << ret[0] << "," << ret[1] << "]" << endl;
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}
