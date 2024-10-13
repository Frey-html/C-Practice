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

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int cnt = 0;
        for(int i = 0;i < nums.size();i++){
            if(nums[i] != val) cnt++;
        }

        std::sort(nums.begin(), nums.end(), [val](const int& a, const int&b)->bool{
            // If 'a' is not equal to 'val' and 'b' is equal to 'val', 'a' should come before 'b'
            if (a != val && b == val) return true;
            // If 'a' is equal to 'val' and 'b' is not equal to 'val', 'b' should come before 'a'
            if (a == val && b != val) return false;
            // Otherwise, maintain the original order (or you can return false to leave them unsorted)
            return false;
        });
        return cnt;
    }
};