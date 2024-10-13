// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=2374 lang=cpp
 * @lcpr version=30204
 *
 * [2374] 边积分最高的节点
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
    int edgeScore(vector<int>& edges) {
        vector<long long int> edgeCalculus(edges.size());
        for(int i = 0; i < edges.size(); i++) {
            edgeCalculus[edges[i]] += i;
        }   

        int maxCalculus = 0;
        int index = -1;   
        for(int i = 0;i < edges.size();i++){
            if(maxCalculus < edgeCalculus[i]){
                maxCalculus = edgeCalculus[i];
                index = i;
            }
        }
        return index;
    }
};
// @lc code=end


// @lcpr-div-debug-arg-start
// funName=edgeScore
// paramTypes= ["number[]"]
// @lcpr-div-debug-arg-end




/*
// @lcpr case=start
// [1,0,0,0,0,7,7,5]\n
// @lcpr case=end

// @lcpr case=start
// [2,0,0,2]\n
// @lcpr case=end

 */

