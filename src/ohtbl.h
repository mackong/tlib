#ifndef OHTBL_H
#define OHTBL_H

#include "common.h"

typedef struct OHTbl_ {
        int positions;
        void *vacated;

        fp_hash hash1, hash2;
        fp_match match;
        fp_destroy destroy;

        int size;
        void **table;
} OHTbl;

int ohtbl_init(OHTbl *htbl, int positions, fp_hash hash1, fp_hash hash2,
               fp_match match, fp_destroy destroy);
int ohtbl_destroy(OHTbl *htbl);
int ohtbl_insert(OHTbl *htbl, const void *data);
int ohtbl_remove(OHTbl *htbl, void **data);
int ohtbl_lookup(const OHTbl *htbl, void **data);

#define ohtbl_size(htbl) ((htbl)->size)

#endif /* OHTBL_H */
