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
