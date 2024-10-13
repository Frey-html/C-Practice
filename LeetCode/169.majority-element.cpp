/*
 * @lc app=leetcode.cn id=169 lang=cpp
 * @lcpr version=30204
 *
 * [169] 多数元素
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
#include <map>
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> count;
        int majority = 0, cnt = 0;
        for(int i = 0;i < nums.size();i++){
            count[nums[i]]++;
            // 如果该数字的出现次数超过当前的majority
            if (count[nums[i]] > cnt) {
                majority = nums[i];  // 更新majority为当前数字
                cnt = count[nums[i]];  // 更新当前最多出现的次数
            }
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [2,2,1,1,1,2,2]\n
// @lcpr case=end

 */

