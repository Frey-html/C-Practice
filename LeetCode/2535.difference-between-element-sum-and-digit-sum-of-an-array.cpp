/*
 * @lc app=leetcode.cn id=2535 lang=cpp
 * @lcpr version=30204
 *
 * [2535] 数组元素和与数字和的绝对差
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
    int differenceOfSum(vector<int>& nums) {
        int elementSum = 0, numericSum = 0;
        int num = 0, temp = 0;
        for(int x : nums){
            elementSum += x;
            num = x;
            while(num > 0){
                numericSum += num % 10;
                num /= 10;
            }
        }
        return abs(elementSum - numericSum);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,15,6,3]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4]\n
// @lcpr case=end

 */

