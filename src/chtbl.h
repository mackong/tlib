#ifndef CHTBL_H
#define CHTBL_H

#include "list.h"

typedef struct CHTbl_ {
        int buckets;

        fp_hash hash;
        fp_match match;
        fp_destroy destroy;

        int size;
        List *table;
} CHTbl;

int chtbl_init(CHTbl *htbl, int buckets, fp_hash hash, fp_match match, fp_destroy destroy);
int chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *html, void **data);
int chtbl_lookup(const CHTbl *htbl, void **data);

#define chtbl_size(htbl) ((htbl)->size)

#endif /* CHTBL_H */
