#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct {
    Node *front, *rear;
    int size;
} LinkedQueue;

void InitQueue(LinkedQueue *q) {
    // 头结点
    Node *head = malloc(sizeof(LinkedQueue));
    head->next = NULL;
    q->front = q->rear = head;
    q->size = 0;
}

bool QueueEmpty(LinkedQueue *q) {
    return q->front == q->rear;
}
int QueueSize(LinkedQueue *q) {
    return q->size;
}
bool EnQueue(LinkedQueue *q, ElemType e) {
    Node *node = malloc(sizeof(LinkedQueue));
    node->data = e;
    node->next = NULL;
    q->rear->next = node;
    q->rear = node;// 指针后移 q->rear = q->rear->next 
    q->size++;
}

bool DeQueue(LinkedQueue *q, ElemType *e) {
    // 空队列
    if(QueueEmpty(q)) {
        return false;
    }
    // 队头元素
    Node *p = q->front->next;
    *e = p->data;

    // 后移头指针
    q->front->next = p->next;

    // 如果队列只有一个元素，出队后需要修改尾指针指向头结点
    if(q->rear == p) {
        q->rear = q->front;
    }

    free(p);
    q->size--;
    return true;
}



int main() {
    ElemType e;
    int i,j;

    LinkedQueue lq, *plq = &lq;
    InitQueue(plq);
    assert(QueueSize(plq) == 0);
    for (i = 0; i < 3; i++) {
        EnQueue(plq, i);
        assert(QueueSize(plq) == i + 1);
    }
    assert(QueueSize(plq) == 3);

    i = 3;
    j=0;
    while (!QueueEmpty(plq)) {
        assert(QueueSize(plq) == i);

        DeQueue(plq, &e);
        assert(e == j);
        i--;
        j++;
    }
    assert(QueueSize(plq) == 0);

    // 此时无法出队
    assert(DeQueue(plq, &e) == false);

    printf("Test successful!!!");
    return 0;
}