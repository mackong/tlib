#include <stdlib.h>
#include <string.h>

#include "sort.h"

int issort(void *data, int size, int esize, fp_compare compare)
{
        char *a = (char *)data;
        char *tmp;
        int i, j;

        if ((tmp = (char *)malloc(esize)) == NULL) {
                return -1;
        }

        for (i = 1; i < size; i++) {
                memcpy(tmp, &a[i * esize], esize);

                j = i - 1;
                while (j >= 0 && compare(&a[j * esize], tmp) > 0) {
                        memcpy(&a[(j + 1) * esize], &a[j * esize], esize);
                        j--;
                }

                memcpy(&a[(j + 1) * esize], tmp, esize);
        }

        free(tmp);

        return 0;
}

static int compare_int(const void *key1, const void *key2)
{
        int tmp1 = *(int *)key1;
        int tmp2 = *(int *)key2;

        if (tmp1 < tmp2) {
                return -1;
        } else if (tmp1 > tmp2) {
                return 1;
        } else {
                return 0;
        }
}

static int partition(void *data, int esize, int i, int k, fp_compare compare)
{
        char *a = (char *)data;
        void *pivot, *tmp;
        int r[3];

        if ((pivot = malloc(esize)) == NULL) {
                return -1;
        }

        if ((tmp = malloc(esize)) == NULL) {
                free(pivot);
                return -1;
        }


        r[0] = (rand() % (k - i + 1)) + i;
        r[1] = (rand() % (k - i + 1)) + i;
        r[2] = (rand() % (k - i + 1)) + i;

        issort(r, 3, sizeof(r[0]), compare_int);

        memcpy(pivot, &a[r[1] * esize], esize);

        while (i < k) {
                while (i < k && compare(&a[k * esize], pivot) > 0) {
                        k--;
                }

                while (i < k && compare(&a[i * esize], pivot) < 0) {
                        i++;
                }

                memcpy(tmp, &a[i * esize], esize);
                memcpy(&a[i * esize], &a[k * esize], esize);
                memcpy(&a[k * esize], tmp, esize);
        }

        free(pivot);
        free(tmp);

        return k;
}

static int qksort_inner(void *data, int size, int esize, int i, int k, fp_compare compare)
{
        int j;

        while (i < k) {
                if ((j = partition(data, esize, i, k, compare)) < 0) {
                        return -1;
                }

                if (qksort_inner(data, size, esize, i, j, compare) < 0) {
                        return -1;
                }

                i = j + 1;
        }

        return 0;
}

int qksort(void *data, int size, int esize, fp_compare compare)
{
        return qksort_inner(data, size, esize, 0, size - 1, compare);
}

static int merge(void *data, int esize, int i, int j, int k, fp_compare compare)
{
        char *a = data;
        char *merged;
        int ipos, jpos, mpos;

        ipos = i;
        jpos = j + 1;
        mpos = 0;

        if ((merged = (char *)malloc(esize * (k - i + 1))) == NULL) {
                return -1;
        }

        while (ipos <= j || jpos <= k) {
                if (ipos > j) {
                        while (jpos <= k) {
                                memcpy(&merged[mpos * esize], &a[jpos * esize], esize);
                                jpos++;
                                mpos++;
                        }
                } else if (jpos > k) {
                        while (ipos <= j) {
                                memcpy(&merged[mpos * esize], &a[ipos * esize], esize);
                                ipos++;
                                mpos++;
                        }
                } else {
                        if (compare(&a[ipos * esize], &a[jpos * esize]) < 0) {
                                memcpy(&merged[mpos * esize], &a[ipos * esize], esize);
                                ipos++;
                                mpos++;
                        } else {
                                memcpy(&merged[mpos * esize], &a[jpos * esize], esize);
                                jpos++;
                                mpos++;
                        }
                }
        }

        memcpy(&a[i * esize], merged, esize * (k - i + 1));

        free(merged);

        return 0;
}

static int mgsort_inner(void *data, int size, int esize, int i, int k, fp_compare compare)
{
        int j;

        if (i < k) {
                j = (i + k - 1) >> 1;

                if (mgsort_inner(data, size, esize, i, j, compare) < 0) {
                        return -1;
                }

                if (mgsort_inner(data, size, esize, j + 1, k, compare) < 0) {
                        return -1;
                }

                if (merge(data, esize, i, j, k, compare) < 0) {
                        return -1;
                }
        }

        return 0;
}

int mgsort(void *data, int size, int esize, fp_compare compare)
{
        return mgsort_inner(data, size, esize, 0, size - 1, compare);
}

int ctsort(int *data, int size, int k)
{
        int *counts, *tmp;
        int i;

        if ((counts = (int *)malloc(k * sizeof(int))) == NULL) {
                return -1;
        }

        if ((tmp = (int *)malloc(size * sizeof(int))) == NULL) {
                return -1;
        }

        memset(counts, 0, k * sizeof(int));

        for (i = 0; i < size; i++) {
                counts[data[i]]++;
        }

        for (i = 1; i < k; i++) {
                counts[i] += counts[i - 1];
        }

        for (i = size - 1; i >= 0; i--) {
                tmp[counts[data[i]] - 1] = data[i];
                counts[data[i]]--;
        }

        memcpy(data, tmp, size * sizeof(int));

        free(counts);
        free(tmp);

        return 0;
}

int rxsort(int *data, int size, int p, int k)
{
        int *counts, *tmp;
        int index, pval, i, n;

        if ((counts = (int *)malloc(k * sizeof(int))) == NULL) {
                return -1;
        }

        if ((tmp = (int *)malloc(size * sizeof(int))) == NULL) {
                return -1;
        }

        for (n = 0; n < p; n++) {
                memset(counts, 0, k * sizeof(int));

                pval = pow(k, n);

                for (i = 0; i < size; i++) {
                        index = (data[i] / pval) % k;
                        counts[index]++;
                }

                for (i = 1; i < k; i++) {
                        counts[i] += counts[i - 1];
                }

                for (i = size - 1; i >= 0; i--) {
                        index = (data[i] / pval) % k;
                        tmp[counts[index] - 1] = data[i];
                        counts[index]--;
                }

                memcpy(data, tmp, size * sizeof(int));
        }

        free(counts);
        free(tmp);

        return 0;
}
