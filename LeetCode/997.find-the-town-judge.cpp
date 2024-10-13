/*
 * @lc app=leetcode.cn id=997 lang=cpp
 * @lcpr version=30204
 *
 * [997] 找到小镇的法官
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
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> trustList(n + 1);
        vector<bool> haveTrustPerson(n + 1, false);
        int mostTrustNum = -1;
        int judgeIndex = -1;
        for(int i = 0;i < trust.size();i++){
            trustList[trust[i][1]]++;
            haveTrustPerson[trust[i][0]] = true;
            if(trustList[trust[i][1]] > mostTrustNum){
                mostTrustNum = trustList[trust[i][1]];
                judgeIndex = trust[i][1];
            }
        }
        if(n == 1 && trust.size() == 0) return 1; 

        if(mostTrustNum == n - 1 && haveTrustPerson[judgeIndex] == false){
            return judgeIndex;
        }
        else return -1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n[[1,2]]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[1,3],[2,3]]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[1,3],[2,3],[3,1]]\n
// @lcpr case=end

 */

