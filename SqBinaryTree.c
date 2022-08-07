#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;

typedef struct TreeNodeData {
    ElemType v;
    bool isNull;  // 是否为空
} TreeNodeData;

// 一颗高度为h的满二叉树共有S=1+2^1+2^2+...+2^(h-1)个结点
// S=2^h - 1
typedef struct SqBinaryTree {
    TreeNodeData *data;
    int size;
    int h;
} SqBinaryTree;

void NewSqBinaryTree(SqBinaryTree *tree, int h) {
    int size = 1 << h - 1 + 1;  // 把序号0空出来
    tree->data = malloc(sizeof(TreeNodeData) * size);
    for (int i = 0; i < size; i++) tree->data[i].isNull = true;
    tree->h = h;
    tree->size = size - 1;  // tree的size记录的是从数组1开始的
}

ElemType *getNodeValue(SqBinaryTree *tree, int node) {
    if (node > tree->size) return NULL;
    TreeNodeData *tnd = tree->data + node;
    if (tnd->isNull) return NULL;
    return &tnd->v;
}

void setNodeValue(SqBinaryTree *tree, int node, ElemType data) {
    TreeNodeData *tnd = tree->data + node;
    tnd->isNull = false;
    tnd->v = data;
}

int getLeft(int node) { return node * 2; }

int getRight(int node) { return node * 2 + 1; }

int getParent(int node) { return node / 2; }

void PreOrderVisit(SqBinaryTree *pst, int root) {
    ElemType *et = getNodeValue(pst, root);
    if (et == NULL) return;
    printf("%d, ", *et);  // 先根
    PreOrderVisit(pst, getLeft(root));
    PreOrderVisit(pst, getRight(root));
}

void InOrderVisit(SqBinaryTree *pst, int root) {
    ElemType *et = getNodeValue(pst, root);
    if (et == NULL) return;
    InOrderVisit(pst, getLeft(root));
    printf("%d, ", *et);
    InOrderVisit(pst, getRight(root));
}

void PostOrderVisit(SqBinaryTree *pst, int root) {
    ElemType *et = getNodeValue(pst, root);
    if (et == NULL) return;
    PostOrderVisit(pst, getLeft(root));
    PostOrderVisit(pst, getRight(root));
    printf("%d, ", *et);
}

int main() {
    SqBinaryTree st, *pst = &st;
    NewSqBinaryTree(pst, 3);
    assert(st.h == 3);
    assert(st.size == 1 + 2 + 4);
    for (int i = 1; i <= 7; i++) {
        assert(getNodeValue(pst, i) == NULL);
        setNodeValue(pst, i, i);
        assert(getNodeValue(pst, i) != NULL);
        assert(*getNodeValue(pst, i) == i);
    }
    printf("二叉树先序遍历预期输出: 1, 2, 4, 5, 3, 6, 7, \n");
    printf("二叉树先序遍历实际输出: ");
    PreOrderVisit(pst, 1);
    printf("\n-------------------------------------------\n");

    printf("二叉树中序遍历预期输出: 4, 2, 5, 1, 6, 3, 7, \n");
    printf("二叉树中序遍历实际输出: ");
    InOrderVisit(pst, 1);
    printf("\n-------------------------------------------\n");

    printf("二叉树中序遍历预期输出: 4, 5, 2, 6, 7, 3, 1, \n");
    printf("二叉树中序遍历实际输出: ");
    PostOrderVisit(pst, 1);
    printf("\n-------------------------------------------\n");

    return 0;
}