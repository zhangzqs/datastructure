#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct {
    ElemType *data;
    int top;
    int maxSize;
} SqStack;

void InitSqStack(SqStack *s, int maxSize) {
    s->data = malloc(sizeof(ElemType) * maxSize);
    s->top = -1;
    s->maxSize = maxSize;
}

bool StackEmpty(SqStack *s) {
    return s->top < 0;
}

bool StackFull(SqStack *s) {
    return s->top >= s->maxSize-1;
}

bool Push(SqStack *s, ElemType e) {
    if(StackFull(s)) {
        return false;
    }
    s->data[++s->top] = e;
    return true;
}

bool Pop(SqStack *s, ElemType *e) {
    if(StackEmpty(s)) {
        return false;
    }
    *e = s->data[s->top--];
    return true;
}

bool GetTop(SqStack *s, ElemType *e) {
        if(StackEmpty(s)) {
        return false;
    }
    *e = s->data[s->top];
    return true;
}

int main() {
    SqStack s1,*ps1=&s1;
    InitSqStack(ps1,10);
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