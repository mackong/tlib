#ifndef SORT_H
#define SORT_H

#include "common.h"

int issort(void *data, int size, int esize, fp_compare compare);

int qksort(void *data, int size, int esize, fp_compare compare);

int mgsort(void *data, int size, int esize, fp_compare compare);

int ctsort(int *data, int size, int k);

int rxsort(int *data, int size, int p, int k);

#endif /* SORT_H */
