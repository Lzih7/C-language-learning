## 从根节点到目标节点的路径
- **后序遍历**离开节点时代码的执行条件
```c
#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

void traverse(BiTNode* root, BiTNode* node, Stack* s, bool* found) {
    if (*found || root == NULL) return;
    
    push(s, root);
    
    if (root == node) {
        *found = true;
        return;
    }
    
    traverse(root->left, node, s, found);
    //if (*found) return;
    
    traverse(root->right, node, s, found);
    if (*found) return;
    
    BiTNode* temp;
    pop(s, &temp);
}

bool path(BiTNode* root, BiTNode* node, Stack* s) {
    if (!root || !node || !s) return false;
    bool found = false;
    traverse(root, node, s, &found);
    return found;
}
```
### 一定要及时return，防止错误的pop
- bool返回值代码
```c
#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

bool traverse(BiTNode* root, BiTNode* target, Stack* s) {
    if (root == NULL) {
        return false;  // 当前路径未找到目标
    }

    push(s, root);  // 当前节点入栈

    if (root == target) {
        return true;  // 找到目标节点
    }

    // 递归查找左子树
    if (traverse(root->left, target, s)) {
        return true;
    }

    // 递归查找右子树
    if (traverse(root->right, target, s)) {
        return true;
    }

    // 左右子树都没找到，当前节点出栈（回溯）
    BiTNode* temp;
    pop(s, &temp);
    return false;
}

bool path(BiTNode* root, BiTNode* target, Stack* s) {
    if (root == NULL || target == NULL || s == NULL) {
        return false;
    }
    return traverse(root, target, s);
}
```
