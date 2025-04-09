## 核心算法
- dfs
- 记忆化
## 例题: 地宫寻宝
### 暴力解法
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
const long NUM=1e9+7;
long path=0;
int grid[50][50];

void dfs(int i,int j,int nums,int val){
    if(i>=n || j>=m || i<0 || j<0 || nums>k) return;
    if(i==n-1 && j==m-1 && nums==k){
        path++;
        return;
    }
    if(grid[i][j]>val){
        dfs(i+1,j,nums,val);
        dfs(i,j+1,nums,val);
        dfs(i+1,j,nums+1,grid[i][j]);
        dfs(i,j+1,nums+1,grid[i][j]);
    }
    else{
        dfs(i+1,j,nums,val);
        dfs(i,j+1,nums,val);
    }
}
int main()
{
    cin >> n >> m >> k;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> grid[i][j];
        }
    }
    dfs(0,0,0,-1);
    path%=NUM;
    cout << path;
    // 请在此输入您的代码
    return 0;
}
```
- 注意判断结束的条件，**最后一个节点也要计入**
### 记忆化
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
const long NUM = 1e9 + 7;
long path = 0;
int grid[50][50];
long memo[50][50][15][15]; // 添加记忆化数组

void dfs(int i, int j, int nums, int val) {
    if (i >= n || j >= m) return;
    
    int current = grid[i][j];
    if (i == n - 1 && j == m - 1) {
        if (nums == k || (nums == k - 1 && current > val)) {
            path++;
        }
        return;
    }
    
    if (current > val) {
        dfs(i + 1, j, nums + 1, current);
        dfs(i, j + 1, nums + 1, current);
    }
    dfs(i + 1, j, nums, val);
    dfs(i, j + 1, nums, val);
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    dfs(0, 0, 0, -1);
    path %= NUM;
    cout << path;
    return 0;
}
```
- 运用`memo`数组记忆化
