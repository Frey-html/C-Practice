/*
 * @lc app=leetcode.cn id=2073 lang=cpp
 * @lcpr version=30204
 *
 * [2073] 买票需要的时间
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
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int cnt = 0;
        for(int i = 0;i <= k;i++){
            if(tickets[i] > tickets[k]){
                cnt += tickets[k];
            }else{
                cnt += tickets[i];
            }
        }

        for(int i = k+1;i < tickets.size();i++){
            if(tickets[i] >= tickets[k]){
                cnt += tickets[k] - 1;
            }else{
                cnt += tickets[i];
            }
        }
        return cnt;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,2]\n2\n
// @lcpr case=end

// @lcpr case=start
// [5,1,1,1]\n0\n
// @lcpr case=end

 */

