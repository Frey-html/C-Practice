// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=189 lang=cpp
 * @lcpr version=30204
 *
 * [189] 轮转数组
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
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();  // 防止 k 大于数组长度
        reverse(nums.begin(), nums.end());  // 反转整个数组
        reverse(nums.begin(), nums.begin() + k);  // 反转前 k 个元素
        reverse(nums.begin() + k, nums.end());  // 反转剩余元素
    }
};


/*
// @lcpr case=start
// [1,2,3,4,5,6,7]\n3\n
// @lcpr case=end

// @lcpr case=start
// [-1,-100,3,99]\n2\n
// @lcpr case=end

 */

