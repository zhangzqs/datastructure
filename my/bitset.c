#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum { ZERO, ONE } Bit;

typedef struct {
    uint8_t *bits;
    uint32_t size;
} BitSet;

void InitBitSet(BitSet *b, uint32_t size) {
    b->size = size;
    size_t n = ((size - 1) / 8) + 1;
    b->bits = (uint8_t *)malloc(sizeof(uint8_t) * n);
    for (int i = 0; i < n; i++) b->bits[i] = 0;
}

Bit GetBitSet(BitSet *b, uint32_t idx) {
    int offset = idx % 8;
    return (b->bits[idx / 8] >> offset) & 1;
}

void SetBitSet(BitSet *b, uint32_t idx, Bit bit) {
    int offset = idx % 8;
    if (bit == ONE)
        b->bits[idx / 8] |= bit << offset;
    else
        b->bits[idx / 8] &= ~(bit << offset);
}

void PrintBitSet(BitSet *b) {
    for (int i = b->size - 1; i >= 0; i--) {
        printf("%d", GetBitSet(b, i));
    }
    printf("\n");
}

uint32_t BitSetToNum(BitSet *b) {
    int n = b->size;
    if (n > 32) n = 32;
    uint32_t res = 0;
    for (int i = 0; i < n; i++) {
        if (GetBitSet(b, i) == ONE) res |= 1 << i;
    }
    return res;
}


int main() {
    BitSet bs, *pbs;
    pbs = &bs;
    InitBitSet(pbs, 10);
    SetBitSet(pbs, 1, ONE);
    PrintBitSet(pbs);
    printf("%d\n", BitSetToNum(pbs));
    return 0;
}