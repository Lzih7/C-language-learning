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
2. 条件判断
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
