/*
 * @lc app=leetcode.cn id=2466 lang=cpp
 * @lcpr version=30204
 *
 * [2466] 统计构造好字符串的方案数
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
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> ans(high + 1, 0);
        ans[0] = 1;
        for(int i = 1;i <= high;i++){
            if(i >= zero) ans[i] += ans[i-zero];
            ans[i] %= (int)1e9 + 7;
            if(i >= one) ans[i] += ans[i-one];
            ans[i] %= (int)1e9 + 7;
        }
        int result = 0;
        for(int i = low;i <= high;i++){
            result += ans[i];
            result %= (int)1e9 + 7;
        }
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n3\n1\n1\n
// @lcpr case=end

// @lcpr case=start
// 2\n3\n1\n2\n
// @lcpr case=end

 */

