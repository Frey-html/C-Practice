/*
 * @lc app=leetcode.cn id=2207 lang=cpp
 * @lcpr version=30204
 *
 * [2207] 字符串中最多数目的子序列
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
    long long maximumSubsequenceCount(string text, string pattern) {
        long long aCount = 0, bCount = 0;
        long long int patterCount = 0;
        for(long long int i = 0;i < text.size();i++){
            if(text[i] == pattern[0]) aCount++;
            if(text[i] == pattern[1]){
                bCount++;
                patterCount += aCount;
            } 
        }
        //special situation
        if(pattern[0] == pattern[1]){
            return aCount * (aCount + 1) / 2;
        }


        
        long long int maxResult = 0; //最大pattern增长
        long long int aPassed = 0, bRemain = bCount;
        long long int currentResult = 0;
        long long int insertA = 0;
        long long int insertB = 0;
        for(long long int i = 0;i <= text.size();i++){
            insertA = bRemain;
            insertB = aPassed;
            currentResult = max(insertA, insertB);
            if(maxResult < currentResult){
                maxResult = currentResult;
            }
            if(i == text.size()) break;
            if(text[i] == pattern[0]) aPassed++;
            if(text[i] == pattern[1]) bRemain--;
        }
        return maxResult + patterCount;
    }
};
// @lc code=end
//参考解，本质上是贪心，加在开头或者结尾一定最优
// class Solution {
// public:
//     //要么加载开头 要么在结尾
//     long long maximumSubsequenceCount(string text, string pattern) {
//         int count1 = 0;
//         int count2 = 0;
//         long long ans  = 0;
//         for(auto c : text){
//             if(c == pattern[1]){
//                 ans += count1;
//                 count2++;
//             }
//             if(c == pattern[0])count1++;
          
//         }
//         return ans + max(count1,count2);
//     }
// };

/*
// @lcpr case=start
// "abdcdbc"\n"ac"\n
// @lcpr case=end

// @lcpr case=start
// "aabb"\n"ab"\n
// @lcpr case=end

 */

