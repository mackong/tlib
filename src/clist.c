#include <stdlib.h>
#include <string.h>

#include "clist.h"

int clist_init(CList *list, void (*destroy) (void *data))
{
        list->size = 0;
        list->head = NULL;
        list->destroy = destroy;

        return 0;
}

int clist_destroy(CList *list)
{
        void *data;

        while (list->size > 0) {
                if (clist_rem_next(list, list->head, (void **)&data) == 0 && list->destroy) {
                        list->destroy(data);
                }
        }
 
        memset(list, 0, sizeof(CList));

        return 0;
}

int clist_ins_next(CList *list, CListElem *element, const void *data)
{
        CListElem *new_element = NULL;

        new_element = (CListElem *)malloc(sizeof(CListElem));
        if (new_element == NULL) {
                return -1;
        }

        new_element->data = (void *)data;

        if (list->size == 0) {
                new_element->next = new_element;
                list->head = new_element;
        } else {
                new_element->next = element->next;
                element->next = new_element;
        }

        list->size++;

        return 0;
}

int clist_rem_next(CList *list, CListElem *element, void **data)
{
        CListElem *old_element = NULL;

        if (list->size == 0) {
                return -1;
        }

        if (element->next == element) {
                old_element = element;
                list->head = NULL;
        } else {
                old_element = element->next;
                element->next = old_element->next;


                if (old_element == list->head) {
                        list->head = old_element->next;
                }
        }

        if (data) {
                *data = old_element->data;
        }

        free(old_element);

        list->size--;

        return 0;
}
