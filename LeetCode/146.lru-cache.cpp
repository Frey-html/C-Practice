/*
 * @lc app=leetcode.cn id=146 lang=cpp
 * @lcpr version=30204
 *
 * [146] LRU 缓存
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

//思路：
//既然要以O（1）get 那必须要用到哈希
//又要O(1) put 那value的结构应该是顺序的，每次put到队首
//然而哈希本身无法实现顺序put，则哈希存指针指向链表，双向链表存value顺序put
//需要unordered_map<int *> (capacity) list<int> (capacity)
//只要list未重新分配空间（超过capacity用allocator申请新的）指针就仍有效
#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

// 定义 Pair 结构体
template <typename K, typename V>
using Pair = pair<K, V>;

class LRUCache {
public:
    LRUCache(int capacity) : _capacity(capacity) {}

    int get(int key) {
        // 检查 key 是否存在于哈希表中
        auto it = _hashMap.find(key);
        if (it == _hashMap.end()) {
            return -1; // Key 不存在，返回 -1
        }
        // 移动访问过的节点到前面
        _myList.splice(_myList.begin(), _myList, it->second);
        return it->second->second; // 返回值
    }
    
    void put(int key, int value) {
        // 如果 key 已存在，更新值并移动到前面
        auto it = _hashMap.find(key);
        if (it != _hashMap.end()) {
            _myList.splice(_myList.begin(), _myList, it->second);
            it->second->second = value; // 更新值
            return;
        }
        
        // 如果超出容量，移除最后一个元素
        if (_myList.size() == _capacity) {
            int lruKey = _myList.back().first; // 获取要移除的 key
            _myList.pop_back(); // 移除最后一个元素
            _hashMap.erase(lruKey); // 从哈希表中删除
        }
        
        // 插入新元素
        _myList.push_front(Pair<int, int>(key, value)); // 添加到前面
        _hashMap[key] = _myList.begin(); // 存储节点迭代器
    }

private:
    unordered_map<int, typename list<Pair<int, int>>::iterator> _hashMap; // key -> iterator
    list<Pair<int, int>> _myList; // 存储 key-value 对
    int _capacity;
};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end



