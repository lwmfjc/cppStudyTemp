/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
#include <vector>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution
{
public:
  vector<int> twoSum(vector<int> &nums, int target)
  {
    auto begin{nums.begin()};
    auto end{nums.end()};
    // 至少有两个元�?
    sort(begin, end);
    for (int i = 0; i < nums.size() - 1; i++)
    {
      int findValue = target - nums[i];
      // 从i+1开始查�?
      auto find = lower_bound(begin + i + 1, end, findValue);
      if (find != end)
      {
        vector<int> result{i, (int)(find - begin)};
        return result;
      }
    }
    return nums;
  }
};
// @lc code=end

void test(int a[])
{
  a = a + 1;

  cout << *a << endl;
}
void test1(char *c)
{
  *(c + 1) = '1';
}
int main(int argc, char const *argv[])
{
  // vector<int> a{3,2,4};
  // Solution solution;
  // auto result = solution.twoSum(a,6);
  // cout << result[0] << endl;
  // cout << result[1] << endl;
  // int k1=65536;
  // int k2=65536;
  // auto  size=65535UL*65536;
  // // vector<int> a(size-1);
  // // cout << a.size() << endl;
  // cout << size <<endl;
  // map<int,int> mp;
  // cout << mp.count(2) << endl;
  // cout << mp[2] << endl;
  // cout << mp.count(2) << endl;
  // int a{3};
  // int b{5};
  // swap(a,b);
  // cout << a << endl;

  int a[]{1, 2, 3, 4, 5};
  // a=a+1;
  //  test(a);

    char * c="Hello"; //字符串常�? 不允许修�?
  char c1[] = "world";
  //  c+1='3';
  /*
  warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
  */
    //  test1(c);     
    // cout << c << endl;

  test1(c1);
  cout << c1 << endl;
  return 0;
}
