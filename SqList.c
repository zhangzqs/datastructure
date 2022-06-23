#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct {
    ElemType *data;
    int length;
    int maxSize;
} SqList;

// 构造一个空的线性表
void InitList(SqList *L, int maxSize) {
    L->maxSize = maxSize;
    L->data = (ElemType *)malloc(sizeof(ElemType) * maxSize);
    L->length = 0;
}

// 求表长
int Length(SqList *L) { return L->length; }

// 按值查找，返回下标，不存在则返回0
int LocateElem(SqList *L, ElemType e) {
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

// 按下标查找元素
ElemType GetElem(SqList *L, int i) { return L->data[i - 1]; }

// 按下标设置元素
void SetElem(SqList *L, int i, ElemType e) { L->data[i - 1] = e; }

// 顺序表插入，插入成功返回true
bool ListInsert(SqList *L, int i, ElemType e) {
    // 存储空间满了
    if (L->length >= L->maxSize) {
        return false;
    }
    // 顺序表可以在原有的[1,L->length]之间插入
    // 也可以再最后的位置新插入一个元素
    if (i < 1 || i > L->length + 1) {
        return false;
    }

    // 将第i个之后的元素后移一次
    for (int j = L->length; j >= i; j--) {
        SetElem(L, j + 1, GetElem(L, j));
    }
    // 插入元素
    SetElem(L, i, e);
    L->length++;
    return true;
}

// 删除元素
bool ListDelete(SqList *L, int i, ElemType *e) {
    if (i < 1 || i > L->length) {
        return false;
    }
    *e = GetElem(L, i);
    for (int j = i; j <= Length(L) - 1; j++) {
        SetElem(L, j, GetElem(L, j + 1));
    }
    L->length--;
    return true;
}

// 输出顺序表
void PrintList(SqList *L) {
    printf("[");
    for (int i = 1; i <= Length(L); i++) {
        ElemType e = GetElem(L, i);
        printf("%d, ", e);
    }

    printf("]\n");
}

// 顺序表是否为空
bool Empty(SqList *L) { return L->length == 0; }

// 销毁顺序表
void DestoryList(SqList *L) { free(L->data); }

int main() {
    SqList sl;
    SqList *L = &sl;
    InitList(L, 10);
    ListInsert(L, 1, 1);
    ListInsert(L, 1, 2);
    ListInsert(L, 1, 3);
    ListInsert(L, 1, 4);
    PrintList(L);
    printf("%d\n", Length(L));
    ElemType e;
    ListDelete(L,2,&e);
    PrintList(L);
    return 0;
}