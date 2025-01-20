/*
 * @lc app=leetcode.cn id=2239 lang=cpp
 * @lcpr version=30204
 *
 * [2239] 找到最接近 0 的数字
 */


// @lcpr-template-start
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cmath>
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int findClosestNumber(vector<int>& nums) {
        int result = nums[0];
        int result_d = abs(nums[0]);
        for(int i = 1;i < nums.size();i++){
            int num = nums[i];
            int num_d = abs(nums[i]);
            if(num_d == result_d){
                result_d = num_d;
                result = num > result ? num : result;
            }else if(num_d < result_d){
                result_d = num_d;
                result = num;
            }
        }
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [-4,-2,1,4,8]\n
// @lcpr case=end

// @lcpr case=start
// [2,-1,1]\n
// @lcpr case=end

 */

