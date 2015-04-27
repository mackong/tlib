#ifndef HEAP_H
#define HEAP_H

#include "common.h"

typedef struct Heap_ {
        int size;

        fp_compare compare;
        fp_destroy destroy;

        void **tree;
} Heap;

int heap_init(Heap *heap, fp_compare compare, fp_destroy destroy);
int heap_destroy(Heap *heap);
int heap_insert(Heap *heap, const void *data);
int heap_extract(Heap *heap, void **data);

#define heap_size(heap) ((heap)->size)

#endif /* HEAP_H */
