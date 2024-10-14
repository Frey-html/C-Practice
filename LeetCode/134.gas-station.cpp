/*
 * @lc app=leetcode.cn id=134 lang=cpp
 * @lcpr version=30204
 *
 * [134] 加油站
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
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        vector<int> value(gas.size()); // value[i] is the gas change from this stop to the next stop 
        for(int i = 0;i < gas.size();i++){
            value[i] = gas[i] - cost[i];
        }
        int back = 0, front = 0; //Two pointer
        int now = 0, lowest = 0; //Current gas and lowest gas in this routine

        now = lowest = value[0];
        while(true){
            if(now < 0){
                if(back == gas.size() - 1)
                    return -1;
                else{
                    while(now < 0){
                        back++;
                        
                    }

                }
            }
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n[3,4,5,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [2,3,4]\n[3,4,3]\n
// @lcpr case=end

 */

