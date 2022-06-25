#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;

typedef struct Node {
    // 数据域
    ElemType data;

    // 指针域
    struct Node *next;
} Node, *LinkedList;

LinkedList NewLinkedList() {
    Node *L = malloc(sizeof(Node));
    L->next = NULL;
    return L;
}

// 在某结点后插入新结点元素
Node *InsertAfter(Node *node, ElemType e){
    Node *n = malloc(sizeof(Node));
    n->data = e;
    n->next = node->next;
    node->next = n;
    return n;
}

// 在某结点后以头插法建立单链表
void HeadInsert(Node* node, ElemType *arr, int size) {
    for(int i=0;i<size;i++){
        InsertAfter(node, arr[i]);
    }
}

// 在某结点后以尾插法建立单链表
void TailInsert(Node* node, ElemType *arr, int size) {
    // 指向尾结点的指针
    Node *r = node;
    for(int i=0;i<size;i++){
        r = InsertAfter(r, arr[i]);
    }
}

Node *GetElem(LinkedList headNode, int i){
    if (i < 0) return NULL;

    Node *n = headNode;
    int j = 0;
    // 当i=3时候
    // j可以取到0, 1, 2，始终小于i=3
    // 即仅当j<i时，才继续循环
    while(n != NULL & j < i) {
        n = n->next;
        j++;
    }
    return n;
}

void PrintList(LinkedList headNode) {
    Node *n = headNode->next;
    printf("[");
    while(n != NULL) {
        printf("%d, ", n->data);
        n = n->next;
    }
    printf("]\n");
}

int main() {
    int arr[] = {1,2,3,4,5};
    LinkedList L = NewLinkedList();
    HeadInsert(L, arr, sizeof(arr)/sizeof(int));
    HeadInsert(L, arr, sizeof(arr)/sizeof(int));
    PrintList(L);
    TailInsert(L, arr, sizeof(arr)/sizeof(int));
    TailInsert(L, arr, sizeof(arr)/sizeof(int));
    PrintList(L);

    Node *node = GetElem(L,6);
    printf("%d\n", node->data);
    return 0;
}