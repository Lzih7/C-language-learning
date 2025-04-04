# 邻接表
## 核心思想
每一个顶点维护一个链表(动态数组)，用于储存邻接点以及边
## 代码实现
eg:
```
      1
    / | \
   2  3  4
     / \
    5   6
```
### 链表表示
```cpp
#include <vector>
#include <list>
using namespace std;

vector<list<pair<int, int>>> adj; // adj[u] = list of {v, weight}

void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w}); // 无向图需双向添加
}

int main() {
    int n = 6; // 顶点数
    adj.resize(n + 1); // 顶点编号1~n

    addEdge(1, 2, 5);
    addEdge(1, 3, 3);
    addEdge(1, 4, 2);
    addEdge(3, 5, 1);
    addEdge(3, 6, 4);

    // 遍历顶点1的邻接点
    for (auto [v, w] : adj[1]) {
        cout << "1 -> " << v << " (weight: " << w << ")\n";
    }
    return 0;
}
```
### 数组表示
```cpp
const int N = 1e5; // 最大顶点数
const int M = 2e5; // 最大边数（无向图要×2）

int h[N], e[M], ne[M], w[M], idx = 0;

void addEdge(int a, int b, int c) {
    e[idx] = b;      // 存储边的终点
    w[idx] = c;      // 存储边的权重
    ne[idx] = h[a];  // 新边的next指向当前头结点
    h[a] = idx++;    // 更新头结点
}

int main() {
    memset(h, -1, sizeof(h)); // 初始化链表头为-1（表示空）

    addEdge(1, 2, 5);
    addEdge(1, 3, 3);
    addEdge(1, 4, 2);
    addEdge(3, 5, 1);
    addEdge(3, 6, 4);

    // 遍历顶点1的邻接边
    for (int i = h[1]; i != -1; i = ne[i]) {
        int v = e[i], weight = w[i];
        cout << "1 -> " << v << " (weight: " << weight << ")\n";
    }
    return 0;
}
```
- 呈现形式(以1为例，即前三个)
```
h[1] → 2 → 1 → 0
e[2]=4, ne[2]=1
e[1]=3, ne[1]=0
e[0]=2, ne[0]=-1
```
