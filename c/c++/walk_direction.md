## 数据结构
- 二维数组
- `dirs={{-1,0},{1,0},{0,-1},{-1,0}}`
- pair<int, int>
### pair相关
pair一般用`{}`表示，用`.first, .second`访问
## 例题
# P1162 填涂颜色

## 题目描述

由数字 $0$ 组成的方阵中，有一任意形状的由数字 $1$ 构成的闭合圈。现要求把闭合圈内的所有空间都填写成 $2$。例如：$6\times 6$ 的方阵（$n=6$），涂色前和涂色后的方阵如下：

如果从某个 $0$ 出发，只向上下左右 $4$ 个方向移动且仅经过其他 $0$ 的情况下，无法到达方阵的边界，就认为这个 $0$ **在闭合圈内**。闭合圈不一定是环形的，可以是任意形状，但保证**闭合圈内**的 $0$ 是连通的（两两之间可以相互到达）。

```plain
0 0 0 0 0 0
0 0 0 1 1 1
0 1 1 0 0 1
1 1 0 0 0 1
1 0 0 1 0 1
1 1 1 1 1 1
```
```plain
0 0 0 0 0 0
0 0 0 1 1 1
0 1 1 2 2 1
1 1 2 2 2 1
1 2 2 1 2 1
1 1 1 1 1 1
```

## 输入格式

每组测试数据第一行一个整数 $n(1 \le n \le 30)$。

接下来 $n$ 行，由 $0$ 和 $1$ 组成的 $n \times n$ 的方阵。

方阵内只有一个闭合圈，圈内至少有一个 $0$。

## 输出格式

已经填好数字 $2$ 的完整方阵。

## 输入输出样例 #1

### 输入 #1

```
6
0 0 0 0 0 0
0 0 1 1 1 1
0 1 1 0 0 1
1 1 0 0 0 1
1 0 0 0 0 1
1 1 1 1 1 1
```

### 输出 #1

```
0 0 0 0 0 0
0 0 1 1 1 1
0 1 1 2 2 1
1 1 2 2 2 1
1 2 2 2 2 1
1 1 1 1 1 1
```
## 题解
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    queue<pair<int, int>> q;
    // Check the four borders for 0s
    for (int i = 0; i < n; ++i) {
        if (grid[i][0] == 0) {
            q.push({i, 0});
            grid[i][0] = 3;
        }
        if (grid[i][n-1] == 0) {
            q.push({i, n-1});
            grid[i][n-1] = 3;
        }
    }
    for (int j = 0; j < n; ++j) {
        if (grid[0][j] == 0) {
            q.push({0, j});
            grid[0][j] = 3;
        }
        if (grid[n-1][j] == 0) {
            q.push({n-1, j});
            grid[n-1][j] = 3;
        }
    }

    // Directions: up, down, left, right
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                grid[nx][ny] = 3;
                q.push({nx, ny});
            }
        }
    }

    // Replace remaining 0s (inside) with 2, and revert 3s to 0s
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0) {
                grid[i][j] = 2;
            } else if (grid[i][j] == 3) {
                grid[i][j] = 0;
            }
        }
    }

    // Output the result
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    solve();
    return 0;
}
```
- 常用**结构化绑定**的方式来访问dirs里的元素
