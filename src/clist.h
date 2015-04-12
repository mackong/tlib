#ifndef CLIST_H
#define CLIST_H

#include "common.h"

typedef struct CListElem_ {
        void *data;
        struct CListElem_ *next;
} CListElem;

typedef struct CList_ {
        int size;
        fp_match match;
        fp_destroy destroy;
        CListElem *head;
} CList;

int clist_init(CList *list, fp_destroy destroy);
int clist_destroy(CList *list);
int clist_ins_next(CList *list, CListElem *element, const void *data);
int clist_rem_next(CList *list, CListElem *element, void **data);
#define clist_size(list) ((list)->size)
#define clist_head(list) ((list)->head)
#define clist_data(element) ((element)->data)
#define clist_next(element) ((element)->next)

#endif /* CLIST_H */
