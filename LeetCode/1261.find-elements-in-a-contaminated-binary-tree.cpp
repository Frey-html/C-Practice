/*
 * @lc app=leetcode.cn id=1261 lang=cpp
 * @lcpr version=30204
 *
 * [1261] 在受污染的二叉树中查找元素
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//可以在净化时直接存哈希，因为题目最终目的是find


class FindElements {
public:
    FindElements(TreeNode* root) {
        if(root != nullptr) root->val = 0;
        clearify(root);
        myRoot = root;
    }

    void clearify(TreeNode* root){
        if(root == nullptr) return;
        int x = root->val;
        if(root->left != nullptr) root->left->val = 2 * x + 1;
        if(root->right != nullptr) root->right->val = 2 * x + 2;
        clearify(root->left);
        clearify(root->right);
    }
    
    bool find(int target) {
        queue<TreeNode* > myQueue;
        myQueue.push(myRoot);
        while(!myQueue.empty()){
            TreeNode* now = myQueue.front();
            myQueue.pop();
            if(now == nullptr) return false;

            if(now->val == target) return true;
            else if(now->val > target) return false;

            if(now->left != nullptr) myQueue.push(now->left);
            if(now->right != nullptr) myQueue.push(now->right);
        }
        return false;
    }
private:
    TreeNode* myRoot;
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
// @lc code=end



/*
// @lcpr case=start
// ["FindElements","find","find"][[[-1,null,-1]],[1],[2]]\n
// @lcpr case=end

// @lcpr case=start
// ["FindElements","find","find","find"][[[-1,-1,-1,-1,-1]],[1],[3],[5]]\n
// @lcpr case=end

// @lcpr case=start
// ["FindElements","find","find","find","find"][[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]\n
// @lcpr case=end

 */

