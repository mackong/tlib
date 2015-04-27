#ifndef SORT_H
#define SORT_H

#include "common.h"

int issort(void *data, int size, int esize, fp_compare compare);

int qksort(void *data, int size, int esize, fp_compare compare);

#endif /* SORT_H */
