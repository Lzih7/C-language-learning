## 普通树转二叉树
### 相关定义
```c
typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;

#define MAX_CHILDREN_NUM 5
struct _CSNode
{
    DataType data;
    struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;

struct __Queue
{
    int i, j; //指向数组内元素的游标
    void **array;
};
typedef struct __Queue Queue;

Queue* create_queue(); //创建队列
bool is_empty_queue(Queue *tree); //队为空返回true,不为空时返回false
void* del_queue(Queue *tree); //结点指针出队
void add_queue(Queue *tree, void *node); //结点指针入队
void free_queue(Queue *tree); //释放队列
```
### 代码
```c
#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过


BiTNode* transform(CSNode *root){
    if(root==NULL){
        return NULL;
    }
    Queue* q=create_queue();
    BiTNode* ans=(BiTNode*)malloc(sizeof(BiTNode));
    ans->data=root->data;
    ans->left=NULL;
    ans->right=NULL;
    add_queue(q,root);
    add_queue(q,ans);
    while(!is_empty_queue(q)){
        CSNode* cs_n=del_queue(q);
        BiTNode* bi_n=del_queue(q);
        BiTNode* pre=NULL;
        int i=0;
        while(cs_n->children[i]!=NULL){
            BiTNode* temp=(BiTNode*)malloc(sizeof(BiTNode));
            temp->data=cs_n->children[i]->data;
            temp->left=NULL;
            temp->right=NULL;
            if(i==0){
                bi_n->left=temp;
                pre=temp;
            }else{
                pre->right=temp;
                pre=temp;
            }
            add_queue(q,cs_n->children[i++]);
            add_queue(q,temp);
        }
    }
    return ans;
}
```
- 利用队列实现BFS
- 此队列可储存**不同类型**的元素
- 用pre节点储存节点的位置
