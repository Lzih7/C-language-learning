## 旋转
旋转是调整**二叉搜索树（BST）**或**自平衡树（如AVL树、红黑树）**的重要操作，主要用于**修复失衡**，确保树的高度保持在合理范围，以提高搜索、插入和删除的效率。

### **1. 右旋（Right Rotation）**
用于**左子树过高**的情况（LL型失衡）。
#### **步骤**
1. 设**根节点 X**的左子节点为**Y**。
2. 让 Y 的**右子树**成为 X 的**左子树**。
3. 将 Y 变为新的根节点，X 成为 Y 的右子树。

#### **代码示例（C++）**
```cpp
struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y; // 返回新的根
}
```

---

### **2. 左旋（Left Rotation）**
用于**右子树过高**的情况（RR型失衡）。
#### **步骤**
1. 设**根节点 X**的右子节点为**Y**。
2. 让 Y 的**左子树**成为 X 的**右子树**。
3. 将 Y 变为新的根节点，X 成为 Y 的左子树。

#### **代码示例（C++）**
```cpp
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y; // 返回新的根
}
```

---

### **3. 左右旋（Left-Right Rotation, LR）**
用于**左子树的右子树导致失衡**的情况：
- **先左旋 X 的左子树**（转为 LL型）
- **再右旋根节点 X**

---

### **4. 右左旋（Right-Left Rotation, RL）**
用于**右子树的左子树导致失衡**的情况：
- **先右旋 X 的右子树**（转为 RR型）
- **再左旋根节点 X**

---
## 高度计算
```cpp
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 递归计算二叉树高度
int treeHeight(TreeNode* root) {
    if (root == NULL) return -1; // 或者返回 0，取决于定义
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 创建新节点
TreeNode* createNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    // 手动构建一个简单的二叉树
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("二叉树的高度: %d\n", treeHeight(root));

    // 释放内存
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

```
