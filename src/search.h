#ifndef SEARCH_H
#define SEARCH_H

#include "common.h"

int bisearch(void *sorted, void *target, int size, int esize, fp_compare compare);

#endif /* SEARCH_H */
