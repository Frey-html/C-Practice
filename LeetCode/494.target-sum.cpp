/*
 * @lc app=leetcode.cn id=494 lang=cpp
 * @lcpr version=30204
 *
 * [494] 目标和
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
    int findTargetSumWays(vector<int>& nums, int target) {
        return dfs(nums, target, 0, 0);
    }

    int dfs(vector<int>& nums, int target, int cnt, int deepth){
        if(deepth == nums.size()){
            int ans = 0;
            for(int i = 0;i < nums.size();i++){
                ans += nums[i];
            }
            if(ans == target) return 1;
            else return 0;
        }else{
            nums[deepth] *= -1;
            cnt += dfs(nums, target, 0, deepth + 1);
            nums[deepth] *= -1;
            cnt += dfs(nums, target, 0, deepth + 1);
        }
        return cnt;
    }
};

int main(){
    vector<int> vec = {1, 1, 1, 1, 1};
    Solution s;
    printf("%d", s.findTargetSumWays(vec, 3));
}
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,1,1]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

 */

