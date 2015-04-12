#include <stdlib.h>
#include <string.h>

#include "chtbl.h"

int chtbl_init(CHTbl *htbl, int buckets, fp_hash hash, fp_match match, fp_destroy destroy)
{
        int i;
        
        htbl->table = (List *)malloc(sizeof(List) * buckets);
        if (htbl->table == NULL) {
                return -1;
        }

        htbl->buckets = buckets;
        for (i = 0; i < buckets; i++) {
                list_init(&htbl->table[i], destroy);
        }

        htbl->hash = hash;
        htbl->match = match;
        htbl->destroy = destroy;
        htbl->size = 0;

        return 0;
}

int chtbl_destroy(CHTbl *htbl)
{
        int i;

        for (i = 0; i < htbl->buckets; i++) {
                list_destroy(&htbl->table[i]);
        }

        free(htbl->table);
        memset(htbl, 0, sizeof(CHTbl));

        return 0;
}

int chtbl_insert(CHTbl *htbl, const void *data)
{
        void *temp;
        int bucket, ret;

        temp = (void *)data;
        if (chtbl_lookup(htbl, &temp) == 0) {
                return 1;
        }

        bucket = htbl->hash(data) % htbl->buckets;
        if ((ret = list_ins_next(&htbl->table[bucket], NULL, data)) == 0) {
                htbl->size++;
        }

        return ret;
}

int chtbl_remove(CHTbl *htbl, void **data)
{
        int bucket;
        ListElem *element, *prev;

        bucket = htbl->hash(data) % htbl->buckets;

        prev = NULL;
        for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {
                if (htbl->match(&data, list_data(element))) {
                        if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
                                htbl->size--;
                                return 0;
                        } else {
                                return -1;
                        }
                }

                prev = element;
        }

        return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data)
{
        ListElem *element;
        int bucket;

        bucket = htbl->hash(*data) % htbl->buckets;
        for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {
                if (htbl->match(*data, list_data(element))) {
                        *data = list_data(element);
                        return 0;
                }
        }

        return -1;
}
