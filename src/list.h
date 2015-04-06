#ifndef LIST_H
#define LIST_H

typedef struct ListElem_ {
        void *data;
        struct ListElem_ *next;
} ListElem;

typedef struct List_ {
        int size;
        int (*match) (const void *key1, const void *key2);
        void (*destroy) (void *data);
        ListElem *head;
        ListElem *tail;
} List;

int list_init(List *list, void (*destroy) (void *data));
int list_destroy(List *list);
int list_ins_next(List *list, ListElem *element, const void *data);
int list_rem_next(List *list, ListElem *element, void **data);
int list_dump(List *list, void (*dump) (const void *data));
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((list)->head == element ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif /* LIST_H */
