# vector
## 初始化
```cpp
#include <vector>

int n = 7, m = 8;

// 初始化一个 int 型的空数组 nums
vector<int> nums;

// 初始化一个大小为 n 的数组 nums，数组中的值默认都为 0
vector<int> nums(n);

// 初始化一个元素为 1, 3, 5 的数组 nums
vector<int> nums{1, 3, 5};

// 初始化一个大小为 n 的数组 nums，其值全都为 2
vector<int> nums(n, 2);

// 初始化一个二维 int 数组 dp
vector<vector<int>> dp;

// 初始化一个大小为 m * n 的布尔数组 dp，
// 其中的值都初始化为 true
vector<vector<bool>> dp(m, vector<bool>(n, true));
```
## 函数
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 10;
    // 数组大小为 10，元素值都为 0
    vector<int> nums(n);
    // 输出 0 (false)
    cout << nums.empty() << endl;
    // 输出：10
    cout << nums.size() << endl;

    // 在数组尾部插入一个元素 20
    nums.push_back(20);
    // 输出：11
    cout << nums.size() << endl;

    // 得到数组最后一个元素的引用
    // 输出：20
    cout << nums.back() << endl;

    // 删除数组的最后一个元素（无返回值）
    nums.pop_back();
    // 输出：10
    cout << nums.size() << endl;

    // 可以通过方括号直接取值或修改
    nums[0] = 11;
    // 输出：11
    cout << nums[0] << endl;

    // 在索引 3 处插入一个元素 99
    nums.insert(nums.begin() + 3, 99);

    // 删除索引 2 处的元素
    nums.erase(nums.begin() + 2);

    // 交换 nums[0] 和 nums[1]
    swap(nums[0], nums[1]);

    // 遍历数组
    // 0 11 99 0 0 0 0 0 0 0
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}
```

# list
- **双向链表**
## 初始化
```cpp
#include <list>

int n = 7;

// 初始化一个空的双向链表 lst
std::list<int> lst;

// 初始化一个大小为 n 的链表 lst，链表中的值默认都为 0
std::list<int> lst(n);

// 初始化一个包含元素 1, 3, 5 的链表 lst
std::list<int> lst{1, 3, 5};

// 初始化一个大小为 n 的链表 lst，其中值都为 2
std::list<int> lst(n, 2);
```
## 函数
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    // 初始化链表
    list<int> lst{1, 2, 3, 4, 5};

    // 检查链表是否为空，输出：false
    cout << lst.empty() << endl;

    // 获取链表的大小，输出：5
    cout << lst.size() << endl;

    // 在链表头部插入元素 0
    lst.push_front(0);
    // 在链表尾部插入元素 6
    lst.push_back(6);

    // 获取链表头部和尾部元素，输出：0 6
    cout << lst.front() << " " << lst.back() << endl;

    // 删除链表头部元素
    lst.pop_front();
    // 删除链表尾部元素
    lst.pop_back();

    // 在链表中插入元素
    auto it = lst.begin();
    // 移动到第三个位置
    advance(it, 2);
    // 在第三个位置插入 99
    lst.insert(it, 99);

    // 删除链表中某个元素
    it = lst.begin();
    // 移动到第二个位置
    advance(it, 1);
    // 删除第二个位置的元素
    lst.erase(it);

    // 遍历链表
    // 输出：1 99 3 4 5
    for (int val : lst) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
```
# queue
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    // 初始化一个空的整型队列 q
    queue<int> q;

    // 在队尾添加元素
    q.push(10);
    q.push(20);
    q.push(30);

    // 检查队列是否为空，输出：false
    cout << q.empty() << endl;

    // 获取队列的大小，输出：3
    cout << q.size() << endl;

    // 获取队列的队头和队尾元素，输出：10 和 30
    cout << q.front() << " " << q.back() << endl;

    // 删除队头元素
    q.pop();

    // 输出新的队头元素：20
    cout << q.front() << endl;

    return 0;
}
```
# stack
```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {

    // 初始化一个空的整型栈 s
    stack<int> s;

    // 向栈顶添加元素
    s.push(10);
    s.push(20);
    s.push(30);

    // 检查栈是否为空，输出：false
    cout << s.empty() << endl;

    // 获取栈的大小，输出：3
    cout << s.size() << endl;

    // 获取栈顶元素，输出：30
    cout << s.top() << endl;

    // 删除栈顶元素
    s.pop();

    // 输出新的栈顶元素：20
    cout << s.top() << endl;

    return 0;
}
```