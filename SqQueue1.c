#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 实现一个不允许浪费空间的环形队列

typedef int ElemType;

typedef struct {
    // 数据数组
    ElemType *data;
    // 数组长度
    int len;

    // 队头指针
    int front;
    // 队尾指针
    int rear;
    // 当前队列大小
    int size;
} SqQueue;

void InitSqQueue(SqQueue *s, int maxSize) {
    s->data = malloc(sizeof(ElemType) * maxSize);
    // 这里不浪费空间了
    s->len = maxSize;
    s->front = 0;
    s->rear = 0;
    s->size = 0;
}

bool QueueEmpty(SqQueue *s) { return s->size==0; }

bool QueueFull(SqQueue *s) { return s->size==s->len; }

bool EnQueue(SqQueue *s, ElemType e) {
    if (QueueFull(s)) {
        return false;
    }

    s->data[s->rear] = e;
    s->rear = (s->rear + 1) % s->len;
    s->size++;
}
bool GetTail(SqQueue *s, ElemType e) {
    if (QueueFull(s)) {
        return false;
    }

    s->data[s->rear] = e;
}

bool DeQueue(SqQueue *s, ElemType *e) {
    if (QueueEmpty(s)) {
        return false;
    }

    *e = s->data[s->front];
    s->front = (s->front + 1) % s->len;
    s->size--;
}

bool GetHead(SqQueue *s, ElemType *e) {
    if (QueueEmpty(s)) {
        return false;
    }

    *e = s->data[s->front];
}


int QueueSize(SqQueue *s) { return s->size; }

int main() {
    ElemType e;
    int i,j;

    SqQueue sq, *psq = &sq;
    InitSqQueue(psq, 3);
    assert(QueueSize(psq) == 0);
    for (i = 0; i < 3; i++) {
        EnQueue(psq, i);
        assert(QueueSize(psq) == i + 1);
    }
    // 此时队满
    assert(QueueFull(psq) == true);
    assert(QueueSize(psq) == 3);

    // 此时无法入队
    assert(EnQueue(psq, 3) == false);

    i = 3;
    j=0;
    while (!QueueEmpty(psq)) {
        assert(QueueSize(psq) == i);

        DeQueue(psq, &e);
        assert(e == j);
        i--;
        j++;
    }
    assert(QueueSize(psq) == 0);

    // 此时无法出队
    assert(DeQueue(psq, &e) == false);

    printf("Test successful!!!");
    return 0;
}