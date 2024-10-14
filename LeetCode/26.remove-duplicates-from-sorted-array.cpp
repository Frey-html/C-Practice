/*
 * @lc app=leetcode.cn id=26 lang=cpp
 * @lcpr version=30204
 *
 * [26] 删除有序数组中的重复项
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
// vector中元素删除erase与迭代起it的性质 官方题解：双指针 时间O（n） 空间O（1）
// class Solution {
// public:
//     int removeDuplicates(vector<int>& nums) {
//         int n = nums.size();
//         if (n == 0) {
//             return 0;
//         }
//         int fast = 1, slow = 1;
//         while (fast < n) {
//             if (nums[fast] != nums[fast - 1]) {
//                 nums[slow] = nums[fast];
//                 ++slow;
//             }
//             ++fast;
//         }
//         return slow;
//     }
// };


// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        map<int, bool> appear;
        for(auto it = nums.begin();it != nums.end();it++){
            if(appear.find(*it) == appear.end()){
                appear[*it] = true;
            }else{
                it = nums.erase(it);
                it--;
            }
        }
        return nums.size();
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,1,2,2,3,3,4]\n
// @lcpr case=end

 */

