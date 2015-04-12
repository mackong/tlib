#include <stdlib.h>
#include <string.h>

#include "ohtbl.h"

static char vacated;

int ohtbl_init(OHTbl *htbl, int positions, fp_hash hash1, fp_hash hash2,
               fp_match match, fp_destroy destroy)
{
        int i;

        htbl->table = (void **)malloc(sizeof(void *) * positions);
        if (htbl->table == NULL) {
                return -1;
        }

        htbl->positions = positions;
        for (i = 0; i < positions; i++) {
                htbl->table[i] = NULL;
        }

        htbl->vacated = &vacated;

        htbl->hash1 = hash1;
        htbl->hash2 = hash2;
        htbl->match = match;
        htbl->destroy = destroy;
        htbl->size = 0;

        return 0;
}

int ohtbl_destroy(OHTbl *htbl)
{
        int i;

        if (htbl->destroy != NULL) {
                for (i = 0; i < htbl->positions; i++) {
                        if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated) {
                                htbl->destroy(htbl->table[i]);
                        }
                }
        }

        free(htbl->table);

        memset(htbl, 0, sizeof(OHTbl));

        return 0;
}

int ohtbl_insert(OHTbl *htbl, const void *data)
{
        void *temp;
        int position, i;

        if (htbl->size == htbl->positions) {
                return -1;
        }

        temp = (void *)data;
        if (ohtbl_lookup(htbl, &temp) == 0) {
                return 1;
        }

        for (i = 0; i < htbl->positions; i++) {
                position = (htbl->hash1(data) + i * htbl->hash2(data)) % htbl->positions;

                if (htbl->table[position] == NULL || htbl->table[position] == htbl->vacated) {
                        htbl->table[position] = (void *)data;
                        htbl->size++;
                        return 0;
                }
        }

        return -1;
}

int ohtbl_remove(OHTbl *htbl, void **data)
{
        int position, i;

        for (i = 0; i < htbl->positions; i++) {
                position = (htbl->hash1(*data) + i * htbl->hash2(*data)) % htbl->positions;

                if (htbl->table[position] == NULL) {
                        return -1;
                } else if (htbl->table[position] == htbl->vacated) {
                        continue;
                } else if (htbl->match(*data, htbl->table[position])) {
                        *data = htbl->table[position];
                        htbl->table[position] = htbl->vacated;
                        htbl->size--;
                        return 0;
                }
        }

        return -1;
}

int ohtbl_lookup(const OHTbl *htbl, void **data)
{
        int position, i;

        for (i = 0; i < htbl->positions; i++) {
                position = (htbl->hash1(*data) + i * htbl->hash2(*data)) % htbl->positions;
                if (htbl->table[position] == NULL) {
                        return -1;
                } else if (htbl->match(htbl->table[position], *data)) {
                        return 0;
                }
        }

        return -1;
}
