/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
    }
};
// @lc code=end
#include <iostream>

//常量指针：落脚点是“指针”，它是一个可以指向别处的指针，只是指向的内容是常量。
//指针常量：落脚点是“常量”，它本质上是一个一旦初始化就生死不改的常量，只是这个常量的类型是指针。
int main(int argc, const char *argv[])
{
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = s.twoSum(nums, target);
    for (int i : result)
    {
        cout << i << " ";
    }
    return 0;
}
