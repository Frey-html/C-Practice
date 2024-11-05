/*
 * @lc app=leetcode.cn id=740 lang=cpp
 * @lcpr version=30204
 *
 * [740] 删除并获得点数
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
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> numsInHash;
        vector<int> numsInVec;
        for(int x : nums){
            if(numsInHash.find(x) == numsInHash.end()){
                numsInVec.push_back(x);
            }
            numsInHash[x] += x;
        }

        sort(numsInVec.begin(), numsInVec.end(), [](const int & a, const int & b)->bool {
            return a <= b;
        });

        int length = numsInVec.back();
        vector<unsigned int> result(length + 1);
        if(numsInHash.find(1) != numsInHash.end()){
            nums[1] = numsInHash[1];
        }

        for(int i = 2; i <= length;i++){
            if(numsInHash.find(i) != numsInHash.end()){
                result[i] = max(result[i-1], result[i-2] + numsInHash[i]);
            }
        }
        return result.back();
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,4,2]\n
// @lcpr case=end

// @lcpr case=start
// [2,2,3,3,3,4]\n
// @lcpr case=end

 */

