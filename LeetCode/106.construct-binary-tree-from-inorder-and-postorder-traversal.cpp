/*
 * @lc app=leetcode.cn id=106 lang=cpp
 * @lcpr version=30204
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        TreeNode* root = recursiveBuild(inorder, postorder, 0, inorder.size()-1, 0, postorder.size()-1);
        return root;
    }

    TreeNode* recursiveBuild(vector<int>& inorder, vector<int>& postorder, int start_in, int end_in, int start_post, int end_post){
        TreeNode* newNode = new TreeNode;
        if(start_in == end_in){
            newNode->val = inorder[start_in];
            return newNode;
        }
        if(start_in < 0 || end_in < 0 || start_in >= inorder.size() || end_in >= inorder.size() || end_post < start_post) return nullptr;


        newNode->val = postorder[end_post];
        auto mid = std::find(inorder.begin() + start_in, inorder.begin() + end_in + 1, newNode->val);
        int mid_index = std::distance(inorder.begin(), mid);

        newNode->left = recursiveBuild(inorder, postorder, start_in, mid_index - 1, start_post, start_post + mid_index - 1 - start_in);
        newNode->right = recursiveBuild(inorder, postorder, mid_index + 1, end_in, start_post + mid_index - start_in, end_post - 1);
        return newNode;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [9,3,15,20,7]\n[9,15,7,20,3]\n
// @lcpr case=end

// @lcpr case=start
// [-1]\n[-1]\n
// @lcpr case=end

 */

