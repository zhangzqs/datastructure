#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;


typedef struct Node {
    // 数据域
    ElemType data;

    // 指针域
    struct Node *next;
} Node, *LinkedStack;


LinkedStack NewLinkedStack() {
    Node *L = malloc(sizeof(Node));
    L->next = NULL;
    return L;
}

bool StackEmpty(LinkedStack s) {
    return s->next == NULL;
}

void Push(LinkedStack s, ElemType e) {
    Node *node = malloc(sizeof(Node));
    node->data = e;
    node->next = s->next;
    s->next = node;
}

void Pop(LinkedStack s, ElemType *e) {
    Node *n = s->next;
    *e = n->data;
    s->next = n->next;
    free(n);
}

void GetTop(LinkedStack s, ElemType *e) {
    *e = s->next->data;
}


int main() {
    LinkedStack ps1=NewLinkedStack();
    printf("入栈序列：");
    for(int i=0;i<10;i++){
        Push(ps1, i);
        printf("%d ",i);
    }
    printf("\n");
    printf("出栈序列：");
    while(!StackEmpty(ps1)) {
        int e;
        Pop(ps1, &e);
        printf("%d ",e);
    }
    printf("\n");
    return 0;
}