#include <stdlib.h>
#include <string.h>

#include "dlist.h"

int dlist_init(DList *list, void (*destroy) (void *data))
{
        list->size = 0;
        list->head = NULL;
        list->tail = NULL;
        list->destroy = destroy;

        return 0;
}

int dlist_destroy(DList *list)
{
        void *data;

        while (list->size != 0) {
                if (dlist_remove(list, list->tail, (void **)&data) == 0 && list->destroy) {
                        list->destroy(data);
                }
        }

        return 0;
}

int dlist_ins_next(DList *list, DListElem *element, const void *data)
{
        DListElem *new_element = NULL;

        if (element == NULL && list->size != 0) {
                return -1;
        }

        new_element = (DListElem *)malloc(sizeof(DListElem));
        if (new_element == NULL) {
                return -1;
        }
        new_element->data = (void *)data;

        if (list->size == 0) {
                new_element->next = NULL;
                new_element->prev = NULL;
                list->head = new_element;
                list->tail = new_element;
        } else {
                new_element->next = element->next;
                new_element->prev = element;

                if (element->next == NULL) {
                        list->tail = new_element;
                } else {
                        element->next->prev = new_element;
                }
                
                element->next = new_element;
        }

        list->size++;

        return 0;
}

int dlist_ins_prev(DList *list, DListElem *element, const void *data)
{
        DListElem *new_element = NULL;

        if (element == NULL && list->size != 0) {
                return -1;
        }

        new_element = (DListElem *)malloc(sizeof(DListElem));
        if (new_element == NULL) {
                return -1;
        }

        new_element->data = (void *)data;

        if (list->size == 0) {
                new_element->next = NULL;
                new_element->prev = NULL;
                list->head = new_element;
                list->tail = new_element;
        } else {
                new_element->next = element;
                new_element->prev = element->prev;

                if (element->prev == NULL) {
                        list->head = new_element;
                } else {
                        element->prev->next = new_element;
                }
                
                element->prev = new_element;
        }

        list->size++;

        return 0;
}

int dlist_remove(DList *list, DListElem *element, void **data)
{
        if (element == NULL || list->size == 0) {
                return -1;
        }
        
        if (element == list->head) {
                list->head = element->next;

                if (list->head == NULL) {
                        list->tail = NULL;
                } else {
                        list->head->prev = NULL;
                }
        } else {
                element->prev->next = element->next;
                if (element->next == NULL) {
                        list->tail = element->prev;
                } else {
                        element->next->prev = element->prev;
                }
        }

        if (data) {
                *data = element->data;
        }
        
        free(element);
        
        list->size--;

        return 0;
}

int dlist_dump(DList *list, void (*dump) (const void *data))
{
        DListElem *p = NULL;

        if (dump == NULL) {
                return -1;
        }

        p = list->head;
        while (p) {
                dump(p->data);
                p = p->next;
        }

        return 0;
}
