#include <stdlib.h>
#include <string.h>

#include "heap.h"

#define heap_parent(i) ((int)(((i) - 1) / 2))
#define heap_left(i) ((int)((i) * 2 + 1))
#define heap_right(i) ((int)((i) * 2 + 2))

int heap_init(Heap *heap, fp_compare compare, fp_destroy destroy)
{
        heap->size = 0;
        heap->compare = compare;
        heap->destroy = destroy;
        heap->tree = NULL;

        return 0;
}

int heap_destroy(Heap *heap)
{
        int i;

        if (heap->destroy) {
                for (i = 0; i < heap->size; i++) {
                        heap->destroy(heap->tree[i]);
                }
        }

        free(heap->tree);

        memset(heap, 0, sizeof(Heap));

        return 0;
}

int heap_insert(Heap *heap, const void *data)
{
        void *tmp;
        int ipos, ppos;

        tmp = (void **)realloc(heap->tree, (heap->size + 1) * sizeof(void *));
        if (tmp) {
                heap->tree = tmp;
        } else {
                return -1;
        }

        heap->tree[heap->size] = (void *)data;

        ipos = heap->size;
        ppos = heap_parent(ipos);

        while (ipos && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {
                tmp = heap->tree[ppos];
                heap->tree[ppos] = heap->tree[ipos];
                heap->tree[ipos] = tmp;

                ipos = ppos;
                ppos = heap_parent(ipos);
        }

        heap->size++;

        return 0;
}

int heap_extract(Heap *heap, void **data)
{
        void *save, *tmp;
        int ipos, lpos, rpos, mpos;
        
        if (heap->size == 0) {
                return -1;
        }

        *data = heap->tree[0];
        
        save = heap->tree[heap->size - 1];

        if (heap->size - 1 > 0) {
                tmp = (void **)realloc(heap->tree, (heap->size - 1) * sizeof(void *));
                if (tmp) {
                        heap->tree = tmp;
                } else {
                        return -1;
                }

                heap->size--;
        } else {
                free(heap->tree);
                heap->tree = NULL;
                heap->size = 0;

                return 0;
        }

        heap->tree[0] = save;

        ipos = 0;

        while (1) {
                lpos = heap_left(ipos);
                rpos = heap_right(ipos);

                if (lpos < heap->size && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0) {
                        mpos = lpos;
                } else {
                        mpos = ipos;
                }

                if (rpos < heap->size && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0) {
                        mpos = rpos;
                }

                if (mpos == ipos) {
                        break;
                } else {
                        tmp = heap->tree[mpos];
                        heap->tree[mpos] = heap->tree[ipos];
                        heap->tree[ipos] = tmp;

                        ipos = mpos;
                }
        }

        return 0;
}
