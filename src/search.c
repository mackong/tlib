#include "search.h"

int bisearch(void *sorted, void *target, int size, int esize, fp_compare compare)
{
        int left, right, middle, ret;

        left = 0;
        right = size - 1;

        while (left <= right) {
                middle = (left + right) >> 1;

                ret = compare((char *)sorted + (esize * middle), target);
                if (ret < 0) {
                        left = middle + 1;
                } else if (ret > 0) {
                        right = middle - 1;
                } else {
                        return middle;
                }
        }

        return -1;
}
