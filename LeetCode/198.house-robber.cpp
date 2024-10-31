/*
 * @lc app=leetcode.cn id=198 lang=cpp
 * @lcpr version=30204
 *
 * [198] 打家劫舍
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
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> best(nums.size());
        if(nums.size() == 1) return nums[0];
        best[0] = nums[0];
        best[1] = max(nums[0], nums[1]);
        for(int i = 2;i < nums.size();i++){
            best[i] = max(nums[i] + best[i-2], best[i-1]);
        }
        return best.back();
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [2,7,9,3,1]\n
// @lcpr case=end

 */

