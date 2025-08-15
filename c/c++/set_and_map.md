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
`std::unordered_map` 是 C++ 标准库中的一个关联容器，用于存储键值对（key-value pairs）。它基于哈希表实现，提供了平均时间复杂度为 O(1) 的查找、插入和删除操作。与 `std::map` 不同，`std::unordered_map` 不会对键进行排序，因此它不保证元素的顺序。

## c++hash的基本用法

#### 1. 头文件
要使用 `std::unordered_map`，首先需要包含头文件 `<unordered_map>`：

```cpp
#include <unordered_map>
```

#### 2. 定义和初始化
你可以定义一个 `std::unordered_map` 并初始化它：

```cpp
std::unordered_map<std::string, int> myMap = {
    {"apple", 2},
    {"banana", 3},
    {"orange", 5}
};
```
注：除了最后一个，都要用`,`间隔；值在前，键在后
#### 3. 插入
可以使用 `insert` 方法或 `[]` 运算符插入元素：

```cpp
myMap.insert({"grape", 4});  // 使用 insert 方法
myMap["pear"] = 6;           // 使用 [] 运算符
```

#### 4. 访问
可以使用 `[]` 运算符或 `at` 方法访问元素：

```cpp
int appleCount = myMap["apple"];  // 使用 [] 运算符
int bananaCount = myMap.at("banana");  // 使用 at 方法
```

注意：如果使用 `[]` 运算符访问不存在的键，会自动插入该键并初始化值为默认值（对于 `int` 是 0）。而 `at` 方法在键不存在时会抛出 `std::out_of_range` 异常。

#### 5. 删除元素
可以使用 `erase` 方法删除元素：

```cpp
myMap.erase("banana");  // 删除键为 "banana" 的元素
```

#### 6. 查找元素
可以使用 `find` 方法查找元素：

```cpp
auto it = myMap.find("orange");
if (it != myMap.end()) {
    std::cout << "Found: " << it->first << " -> " << it->second << std::endl;
} else {
    std::cout << "Not found" << std::endl;
}
```

#### 7. 遍历元素
可以使用迭代器或范围-based for 循环遍历 `std::unordered_map`：

运用**迭代器**
```cpp
// 使用迭代器
for (auto it = myMap.begin(); it != myMap.end(); ++it) {
    std::cout << it->first << " -> " << it->second << std::endl;
}

// 使用范围-based for 循环
for (const auto& pair : myMap) {
    std::cout << pair.first << " -> " << pair.second << std::endl;
}
```

### 其他常用操作

#### 1. 获取大小
可以使用 `size` 方法获取 `std::unordered_map` 中元素的数量：

```cpp
std::size_t size = myMap.size();
```

#### 2. 检查是否为空
可以使用 `empty` 方法检查 `std::unordered_map` 是否为空：

```cpp
if (myMap.empty()) {
    std::cout << "The map is empty" << std::endl;
}
```

#### 3. 清空容器
可以使用 `clear` 方法清空 `std::unordered_map`：

```cpp
myMap.clear();
```

### 自定义哈希函数和比较函数

`std::unordered_map` 允许你自定义哈希函数和比较函数。默认情况下，它使用 `std::hash` 和 `std::equal_to`，但你可以为自定义类型提供自己的实现。

```cpp
struct MyKey {
    int id;
    std::string name;
};

struct MyKeyHash {
    std::size_t operator()(const MyKey& k) const {
        return std::hash<int>()(k.id) ^ std::hash<std::string>()(k.name);
    }
};

struct MyKeyEqual {
    bool operator()(const MyKey& lhs, const MyKey& rhs) const {
        return lhs.id == rhs.id && lhs.name == rhs.name;
    }
};

std::unordered_map<MyKey, int, MyKeyHash, MyKeyEqual> customMap;
```

### 性能考虑

- **哈希冲突**：`std::unordered_map` 的性能依赖于哈希函数的质量。如果哈希函数导致大量冲突，性能会下降。
- **负载因子**：负载因子是容器中元素数量与桶数量的比值。你可以通过 `max_load_factor` 方法来调整负载因子，以平衡内存使用和性能。

```cpp
myMap.max_load_factor(0.7);  // 设置最大负载因子为 0.7
myMap.rehash(100);  // 重新哈希，设置桶的数量至少为 100
```

### 总结

`std::unordered_map` 是一个高效的关联容器，适用于需要快速查找、插入和删除的场景。它不保证元素的顺序，但提供了平均 O(1) 时间复杂度的操作。你可以通过自定义哈希函数和比较函数来适应不同的键类型。

## 子字符串
```cpp
s.substr(i, len)
```
i: 开始处的下标

len: 长度
+ string头文件
