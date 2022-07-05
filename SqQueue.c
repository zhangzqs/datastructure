#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
} SqQueue;

void InitSqQueue(SqQueue *s, int maxSize) {
    s->data = malloc(sizeof(ElemType) * maxSize);
    s->len = maxSize + 1;
    s->front = 0;
    s->rear = 0;
}

bool QueueEmpty(SqQueue *s) { return s->front == s->rear; }

bool QueueFull(SqQueue *s) { return s->front == (s->rear + 1) % s->len; }

bool EnQueue(SqQueue *s, ElemType e) {
    if (QueueFull(s)) {
        return false;
    }

    s->data[s->rear] = e;
    s->rear = (s->rear + 1) % s->len;
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
}

bool GetHead(SqQueue *s, ElemType *e) {
    if (QueueEmpty(s)) {
        return false;
    }

    *e = s->data[s->front];
}

int QueueSize(SqQueue *s) { return (s->len + s->rear - s->front) % s->len; }

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