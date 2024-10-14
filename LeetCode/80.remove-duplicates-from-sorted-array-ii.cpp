// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=80 lang=cpp
 * @lcpr version=30204
 *
 * [80] 删除有序数组中的重复项 II
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
//对于中等难度以上的题，第一次遇到理清思路，写好注释慢慢写比直接上手重要

//官方题解 仍是快慢双指针，不过slow指向已经处理完元素的后一个，fast与slow-2判断fast元素是否应当保留
//此处一个个判断时，不需要在fast处成组计数，因为已经被复制的部分保留了计数信息
//自己没有充分利用信息而去成组复制
// class Solution {
// public:
//     int removeDuplicates(vector<int>& nums) {
//         int n = nums.size();
//         if (n <= 2) {
//             return n;
//         }
//         int slow = 2, fast = 2;
//         while (fast < n) {
//             if (nums[slow - 2] != nums[fast]) {
//                 nums[slow] = nums[fast];
//                 ++slow;
//             }
//             ++fast;
//         }
//         return slow;
//     }
// };

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //维护first, first_end  now， now_end四个指针
        //frist指针每次向后探寻，计量相同的元素数，将每一个数字不超过2的个数复制到now
        //now从第一次出现三个连续数字的第三个处开始，接受first的覆盖
        int first = 1, first_end = 1, now = 0, now_end = 0;
        int length = nums.size();
        if(length <= 2) return length;

        //设定起始位置 从first向now复制需要now先找到第一组连续三个重复的数字
        while(now < length){
            int cnt = 0;
            while(now_end < length && nums[now_end] == nums[now]){
                cnt++;
                now_end++;
            }

            //第一组可能的三个重复数字为最大的数字，可以直接返回不必从后向前覆盖
            if(now_end == length)
            {
                if(cnt >= 2)
                    return now + 2;
                else 
                    return now + cnt;
            }

            //检测这一组是否出现三个以上重复数字，如果出现则first可以开始工作，否则now移动到now_end处继续向后试探
            if(cnt > 2){
                now += 2;
                break;
            }
            
            now = now_end;
        }

        first = now_end, first_end = now_end;
        //此时now_end为first目标位置，即在第一组三个连续数字的下一组起始
        while(first < length){
            int cnt = 0;
            //当first_end=length时做完最后一次复制，退出循环
            while(first_end < length && nums[first_end] == nums[first]){
                cnt++;
                first_end++;
            }

            //检测这一组是否出现三个以上重复数字，如果出现则仅从now的位置向后复制两位
            if(cnt > 2){
                cnt = 2;
            }
            for(int i = 0;i < cnt;i++){
                nums[now + i] = nums[first];
            }
            //向后移动now，进入下一个循环，first继续向后试探
            now += cnt;
            first = first_end;
        }
        return now;
    }
};

// int main(){
//     Solution s = Solution();
//     vector<int> nums = {0,0,1,1,1,1,2,3,3};
//     s.removeDuplicates(nums);
// }
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,2,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,1,1,2,3,3]\n
// @lcpr case=end

 */

