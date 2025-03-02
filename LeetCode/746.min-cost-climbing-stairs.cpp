/*
 * @lc app=leetcode.cn id=746 lang=cpp
 * @lcpr version=30204
 *
 * [746] 使用最小花费爬楼梯
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
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> minCost(cost.size() + 1);
        if(cost.size() <= 2) return min(cost[0], cost[1]); 
        minCost[0] = 0;
        minCost[1] = 0;
        for(int i = 2;i <= cost.size();i++){
            minCost[i] = min(minCost[i-1] + cost[i-1], minCost[i-2] + cost[i-2]);
        }
        return minCost.back();
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,15,20]\n
// @lcpr case=end

// @lcpr case=start
// [1,100,1,1,1,100,1,1,100,1]\n
// @lcpr case=end

 */

