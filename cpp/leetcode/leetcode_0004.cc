// 寻找两个正序数组中的中位数
// 要求：时间复杂度为O(log(m+n))
// 2024-10-31

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void PrintVectorNumber(vector<int> &vec) {
  vector<int>::iterator it;

  cout << "vector: ";
  for (it = vec.begin(); it < vec.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

// 提交代码: -----------------------------------------------------------------//
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      vector<int> nums;
      // 合并向量
      nums.insert(nums.end(), nums1.begin(), nums1.end());
      nums.insert(nums.end(), nums2.begin(), nums2.end());
      // 创建最小堆
      make_heap(nums.begin(), nums.end(), greater<int>());

      int total_size = nums.size();
      int left_index = ceil(total_size / 2);
      int left;
      for (int i = 0; i < left_index; i++) {
        left = nums[0];
        // 堆弹出顶部元素，剩余数据仍按堆存储
        pop_heap(nums.begin(), nums.end(), greater<int>());
        nums.pop_back();
      }
      if (total_size % 2 == 0) {
        return (left + nums[0]) / 2.0;
      } else {
        return nums[0];
      }
    }
};

// 本地测试: -----------------------------------------------------------------//
void Test01(void) {
  vector<int> nums1 = {1, 3};
  vector<int> nums2 = {2};
  Solution sol;

  cout << __func__ << ": -------------------------------------------" << endl;
  double median = sol.findMedianSortedArrays(nums1, nums2);
  cout << "median(2): " << median << endl;
}

void Test02(void) {
  vector<int> nums1 = {1, 2};
  vector<int> nums2 = {3, 4};
  Solution sol;

  cout << __func__ << ": -------------------------------------------" << endl;
  double median = sol.findMedianSortedArrays(nums1, nums2);
  cout << "median(2.5): " << median << endl;
}

int main(void)
{
  Test01();
  Test02();

  return 0;
}
