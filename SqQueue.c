#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

    SqQueue sq,*psq=&sq;
    InitSqQueue(psq, 3);
    for(int i=0;i<3;i++) {
        EnQueue(psq, i);
    }
    // 此时队满
    assert(QueueFull(psq) == true);
    // 此时无法入队
    assert(EnQueue(psq, 3) == false);
    
    while(!QueueEmpty(psq)) {
        DeQueue(psq,&e);
        printf("%d ",e);
    }
    printf("\n");

    // 此时无法出队
    assert(DeQueue(psq, &e) == false);
    return 0;
}