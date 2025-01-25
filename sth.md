## unordered_set的使用
- 基本义为**无序、可快速查找的容器**，本质是哈希表

### 特性
1. **插入元素**：使用 `insert()` 方法插入元素。如果插入重复元素，则插入失败。
2. **查找元素**：使用 `find()` 方法查找元素。返回一个迭代器，如果元素不存在则返回 `end()`。
3. **删除元素**：可以使用 `erase()` 删除指定元素或迭代器指向的元素。
4. **哈希函数**：`unordered_set` 默认使用 `std::hash` 提供的哈希函数。如果需要，可以自定义哈希函数和比较函数。
5. **是否存在**：`count()`用于检测特定元素是否存在于set中，用于条件判断

### 基本语法

```cpp
#include <iostream>
#include <unordered_set>

int main() {
    // 创建一个 unordered_set
    std::unordered_set<int> mySet;

    // 插入元素
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);
    mySet.insert(10); // 重复的值不会插入

    // 遍历元素
    for (int val : mySet) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 查找元素
    if (mySet.find(20) != mySet.end()) {
        std::cout << "20 在集合中" << std::endl;
    }

    // 删除元素
    mySet.erase(20);

    // 检查大小
    std::cout << "集合大小: " << mySet.size() << std::endl;

    return 0;
}
```
