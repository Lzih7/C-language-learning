# 回溯
核心：递归和和试探

当问题不满足条件时，则return回上一层，继续尝试其他路径

基本框架
-
```
bool backtrack(参数) {
    if (满足结束条件) {
        处理解并返回;
    }
    
    for (选择 in 选择列表) {
        做出选择;
        backtrack(路径);  // 递归进行下一步选择
        撤销选择;  // 回溯，撤销之前的选择
    }
}
```
## 关键点
1. 选择
2. 条件判断: 一定要返回！
3. 撤销选择：路径不合适时，return到上一级，尝试其他路径

## 常见问题
+ N皇后问题
```
#define N 8  //宏定义之后可直接使用
bool issafe(int board[N][N],int row,int col){
    //检查列
    for(int i=0;i<n;i++){
        if(board[i][col]) return false;
    }
    // 检查左上对角线
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // 检查右上对角线
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

bool solvequeen(int board[N][N],int row){
    if (row >= N) {
        return true;  // 如果所有皇后都放置完毕，返回 true
    }

    // 在当前行的每一列尝试放置皇后
    for (int col = 0; col < N; col++) {
        if (issafe(board, row, col)) {
            board[row][col] = 1;  // 放置皇后

            if (solvequeen(board, row + 1)) {
                return true;  // 如果能成功放置所有皇后，返回 true
            }

            board[row][col] = 0;  // 回溯，撤销放置; 
        }
    }

    return false;  // 无法放置皇后，返回 false
}
```
+ **row从零开始**
+ **solvequeen()返回一个bool类型的值，表示在N*N的棋盘上是否存在**
+ **在print数组时，检测board[i][j]的值来判断输出什么值**

---
+ 电话号码--->含for循环
```
/*抄的代码*/
class Solution {
    string MAP[10] = {"",    "",    "abc",  "def", "ghi",
                      "jkl", "mno", "pqrs", "tuv", "wxyz"};

public:
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        if (n == 0) {
            return {};
        }
        vector<string> ans;
        string path(n, 0);
        std::function<void(int)> dfs;
        dfs = [&](int i) {
            if (i == n) {
                ans.emplace_back(path); // 在末尾直接添加一个元素
                return;
            }
            for (char c : MAP[digits[i] - '0']) {
                path[i] = c;
                dfs(i + 1); // 递归调用
            }
        };
        dfs(0);
        return ans;
    }
};
// 经典回溯，但此题不需撤销选择
```
+ 用MAP数组存储对应关系
+ 关注dfs中参数的具体含义

---
+ 括号生成
```
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        int m=2*n;
        vector<string> ans;
        string path(m,0);
        std::function<void(int,int)> dfs;
        dfs=[&](int i,int open){
            if(i==m){
                ans.emplace_back(path);
                return;
            }
            if(open<n){
                path[i]='(';
                dfs(i+1,open+1);
            }
            if(i-open<open){
                path[i]=')';
                dfs(i+1,open);
            }
        };
        dfs(0,0);
        return ans;
    }
};
/*抄的回溯*/
```
---
+ 组合总和
```
/*先确定dfs的参数*/
/*可以优化*/
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> path;

        function<void(int, int)> dfs; // 函数包装器
        dfs = [&](int i, int left) {
            if (left == 0) {
                ans.emplace_back(path);
                return;
            }
            if (i == candidates.size() || left < 0) {
                return; // 失败
            }
            dfs(i + 1, left); // 不选

            path.emplace_back(candidates[i]); // 选
            dfs(i, left - candidates[i]);
            path.pop_back();
        };
        dfs(0, target);
        return ans;
    }
};
```
