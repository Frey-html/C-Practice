// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=2266 lang=cpp
 * @lcpr version=30204
 *
 * [2266] 统计打字方案数
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
    int countTexts(string pressedKeys) {
        int maxSubsequenceLength = 0;
        typedef pair<int, int> subString;
        vector<subString> inputString;
        int three[3] = {1, 2, 3};
        int four[4] = {1, 2, 3, 4};
        vector<int> resultSequence;

        int start = 0, end = start + 1;
        if(pressedKeys.length() == 1) return 1;
        while(start < pressedKeys.length()){
            subString s;
            s.first = pressedKeys[start] - '0';
            while(end < pressedKeys.length() && pressedKeys[start] == pressedKeys[end]){
                end++;
            }
            int length = end - start;
            if(length > maxSubsequenceLength) maxSubsequenceLength = length;
            s.second = length;
            inputString.push_back(s);
            
            start = end;
            end = start + 1;
        }

        //do dp 
        vector<int> dp3(maxSubsequenceLength + 1, 0);
        vector<int> dp4(maxSubsequenceLength + 1, 0);
        dp3[0] = dp4[0] = 1;
        for(int i = 1;i <= maxSubsequenceLength;i++){
            for(int x : three){
                if(i >= x){
                    dp3[i] += dp3[i-x];
                    dp3[i] %= (int)1e9 + 7;
                }
            }
            for(int x : four){
                if(i >= x){
                    dp4[i] += dp4[i-x];
                    dp4[i] %= (int)1e9 + 7;
                }
            }
        }


        //count possibility for substring
        for(subString s : inputString){
            if(s.first == 7 || s.first == 9){
                resultSequence.push_back(dp4[s.second]);
            }else{
                resultSequence.push_back(dp3[s.second]);
            }
        }

        //calculate result
        long long int ans = 1;
        for(int x : resultSequence){
            ans *= x;
            ans %= (int)1e9 + 7;
        }
        return ans;
    }
};
// @lc code=end


// @lcpr-div-debug-arg-start
// funName=countTexts
// paramTypes= ["string"]
// @lcpr-div-debug-arg-end




/*
// @lcpr case=start
// "22233"\n
// @lcpr case=end

// @lcpr case=start
// "222222222222222222222222222222222222"\n
// @lcpr case=end

 */

