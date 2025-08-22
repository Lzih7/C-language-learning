# 优先队列
## 1. 什么是优先队列？

`priority_queue` 是 C++ 标准模板库（STL）中的一种**容器适配器**。它与普通队列 `queue` 的最大区别在于：元素出队的顺序不是「先进先出」（FIFO），而是**优先级最高的元素最先出队**。

### 生活中的比喻：
- **普通队列**：像在超市排队结账，先来的人先结账。
- **优先队列**：像医院急诊科，病情最危急的病人（优先级最高）优先得到救治，无论他是什么时候来的。

## 2. 底层实现原理

`priority_queue` 的底层通常使用 **堆（Heap）** 数据结构来实现，具体来说是 **二叉堆（Binary Heap）**。

- **大顶堆（Max-Heap）**：父节点的值大于或等于其子节点的值。根节点是最大值。
- **小顶堆（Min-Heap）**：父节点的值小于或等于其子节点的值。根节点是最小值。

这种实现保证了插入和删除操作的时间复杂度都是 **O(log n)**，而获取最高优先级元素（堆顶）的时间复杂度是 **O(1)**。

## 3. 模板参数详解

`priority_queue` 的完整声明形式如下：

```cpp
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
```

### 三个模板参数：
1. **`T`**：队列中存储的元素类型（如 `int`, `string`, 自定义类等）
2. **`Container`**：底层容器类型，必须是支持 `front()`, `push_back()`, `pop_back()` 等操作的序列容器，默认为 `vector<T>`
3. **`Compare`**：比较函数/函数对象，用于确定元素的优先级顺序，默认为 `std::less<T>`（大顶堆）

## 4. 创建 priority_queue 的几种方式

### 4.1 默认创建（大顶堆）
```cpp
// 存储int的大顶堆，最大的元素在顶部
priority_queue<int> max_heap;

// 存储string的大顶堆，按字典序最大的在顶部
priority_queue<string> str_max_heap;
```

### 4.2 创建小顶堆
```cpp
// 方法1：使用 greater<>
priority_queue<int, vector<int>, greater<int>> min_heap;

// 方法2：存储string的小顶堆，字典序最小的在顶部
priority_queue<string, vector<string>, greater<string>> str_min_heap;
```

### 4.3 使用自定义比较器
```cpp
// 自定义比较函数
struct CompareLength {
    bool operator()(const string& a, const string& b) {
        return a.length() < b.length(); // 长度大的优先级高
    }
};

// 按字符串长度排序的大顶堆
priority_queue<string, vector<string>, CompareLength> length_heap;
```

## 5. 常用成员函数

| 函数 | 功能描述 | 时间复杂度 |
|------|----------|------------|
| `push(const T& value)` | 插入元素 | O(log n) |
| `emplace(Args&&... args)` | 原地构造并插入元素 | O(log n) |
| `pop()` | 移除堆顶元素 | O(log n) |
| `top()` | 访问堆顶元素（不移除） | O(1) |
| `size()` | 返回元素数量 | O(1) |
| `empty()` | 判断是否为空 | O(1) |

**注意**：`priority_queue` 没有 `clear()` 函数，需要清空时只能循环 `pop()`。

## 6. 代码示例

### 示例 1：基本使用（整数）
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    // 默认大顶堆
    priority_queue<int> pq;
    
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);
    
    cout << "大顶堆顺序: ";
    while (!pq.empty()) {
        cout << pq.top() << " "; // 输出: 50 30 20 10
        pq.pop();
    }
    cout << endl;
    
    // 小顶堆
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(30);
    min_pq.push(10);
    min_pq.push(50);
    min_pq.push(20);
    
    cout << "小顶堆顺序: ";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " "; // 输出: 10 20 30 50
        min_pq.pop();
    }
    
    return 0;
}
```

### 示例 2：字符串排序
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

int main() {
    // 字符串大顶堆（字典序降序）
    priority_queue<string> str_pq;
    str_pq.push("banana");
    str_pq.push("apple");
    str_pq.push("cherry");
    str_pq.push("date");
    
    cout << "字典序降序: ";
    while (!str_pq.empty()) {
        cout << str_pq.top() << " "; // date cherry banana apple
        str_pq.pop();
    }
    cout << endl;
    
    // 字符串小顶堆（字典序升序）
    priority_queue<string, vector<string>, greater<string>> str_min_pq;
    str_min_pq.push("banana");
    str_min_pq.push("apple");
    str_min_pq.push("cherry");
    str_min_pq.push("date");
    
    cout << "字典序升序: ";
    while (!str_min_pq.empty()) {
        cout << str_min_pq.top() << " "; // apple banana cherry date
        str_min_pq.pop();
    }
    
    return 0;
}
```

### 示例 3：自定义比较器
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// 按字符串长度排序，长度长的优先级高
struct CompareByLength {
    bool operator()(const string& a, const string& b) {
        return a.length() < b.length();
    }
};

int main() {
    priority_queue<string, vector<string>, CompareByLength> length_pq;
    
    length_pq.push("apple");
    length_pq.push("banana");
    length_pq.push("cherry");
    length_pq.push("kiwi");
    length_pq.push("strawberry");
    
    cout << "按长度降序: ";
    while (!length_pq.empty()) {
        cout << length_pq.top() << " "; // strawberry banana cherry apple kiwi
        length_pq.pop();
    }
    
    return 0;
}
```

## 7. 性能特点和应用场景

### 优点：
- **高效**：插入和删除都是 O(log n)，获取最大值/最小值是 O(1)
- **灵活**：可以通过自定义比较器实现各种优先级规则
- **自动排序**：元素自动按优先级排序

### 应用场景：
1. **任务调度**：操作系统进程调度
2. **Dijkstra 算法**：寻找最短路径
3. **Huffman 编码**：数据压缩
4. **合并 K 个有序链表**
5. **获取前 K 个最大/最小元素**
6. **模拟系统**：事件驱动模拟

## 8. 注意事项

1. **迭代器**：`priority_queue` 不提供迭代器，不能遍历所有元素
2. **稳定性**：相同优先级的元素，出队顺序是不确定的
3. **底层访问**：不能直接访问底层容器
4. **异常安全**：`push()` 和 `pop()` 提供基本异常保证

## 总结

`priority_queue` 是一个功能强大且高效的容器适配器，通过堆数据结构实现了快速的优先级访问。理解其底层原理和比较器的使用方式，可以让你在解决各种算法问题时游刃有余。