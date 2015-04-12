#include <stdlib.h>
#include <string.h>

#include "list.h"

int list_init(List *list, fp_destroy destroy)
{
        list->size = 0;
        list->head = NULL;
        list->tail = NULL;
        list->destroy = destroy;

        return 0;
}

int list_destroy(List *list)
{
        void *data;

        while (list->size) {
                if (list_rem_next(list, NULL, &data) == 0 && list->destroy) {
                        list->destroy(data);
                }
        }

        memset(list, 0, sizeof(List));

        return 0;
}

int list_ins_next(List *list, ListElem *element, const void *data)
{
        ListElem *new_element = NULL;

        new_element = (ListElem *)malloc(sizeof(ListElem));
        if (new_element == NULL) {
                return -1;
        }
        new_element->data = (void *)data;

        if (element == NULL) {
                if (list->head == NULL) {
                        list->tail = new_element;
                }
                
                new_element->next = list->head;
                list->head = new_element;
        } else {
                if (element->next == NULL) {
                        list->tail = new_element;
                }

                new_element->next = element->next;
                element->next = new_element;
        }

        list->size++;

        return 0;
}

int list_rem_next(List *list, ListElem *element, void **data)
{
        ListElem *old_element = NULL;
        
        if (list->size == 0) {
                return -1;
        }

        if (element == NULL) {
                old_element = list->head;
                list->head = list->head->next;
                if (list->size == 1) {
                        list->tail = NULL;
                }
        } else {
                if (element->next == NULL) {
                        return -1;
                }
                
                old_element = element->next;
                element->next = element->next->next;
                if (element->next == NULL) {
                        list->tail = element;
                }
        }

        if (data) {
                *data = old_element->data;
        }
        
        free(old_element);
        
        list->size--;
        
        return 0;
}

int list_dump(List *list, void (*dump) (const void *data))
{
        ListElem *p = NULL;

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
