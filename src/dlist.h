#ifndef DLIST_H
#define DLIST_H

typedef struct DListElem_ {
        void *data;
        struct DListElem_ *prev;
        struct DListElem_ *next;
} DListElem;

typedef struct DList {
        int size;
        int (*match) (const void *key1, const void *key2);
        void (*destroy) (void *data);
        DListElem *head;
        DListElem *tail;
} DList;

int dlist_init(DList *list, void (*destroy) (void *data));
int dlist_destroy(DList *list);
int dlist_ins_next(DList *list, DListElem *element, const void *data);
int dlist_ins_prev(DList *list, DListElem *element, const void *data);
int dlist_remove(DList *list, DListElem *element, void **data);
int dlist_dump(DList *list, void (*dump) (const void *data));
#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

#endif /* DLIST_H */
