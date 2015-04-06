#include <stdlib.h>

#include "set.h"

int set_init(Set *set, int (*match)(const void *key1, const void *key2),
             void (*destroy)(void *data))
{
        int ret = 0;
        
        ret = list_init(set, destroy);
        set->match = match;

        return ret;
}

int set_insert(Set *set, const void *data)
{
        if (set_is_member(set, data)) {
                return 1;
        }

        return list_ins_next(set, list_tail(set), data);
}


int set_remove(Set *set, void **data)
{
        ListElem *member, *prev;

        prev = NULL;
        member = list_head(set);

        while (member) {
                if (set->match(*data, list_data(member))) {
                        break;
                }

                prev = member;
                member = list_next(member);
        }

        if (member == NULL) {
                return -1;
        }

        return list_rem_next(set, prev, data);
}

int set_union(Set *setu, const Set *set1, const Set *set2)
{
        ListElem *member;
        
        if (set_init(setu, set1->match, NULL) != 0) {
                return -1;
        }

        member = list_head(set1);
        while (member) {
                if (set_insert(setu, list_data(member)) != 0) {
                        set_destroy(setu);
                        return -1;
                }

                member = list_next(member);
        }

        member = list_head(set2);
        while (member) {
                if (!set_is_member(setu, list_data(member))) {
                        if (set_insert(setu, list_data(member)) != 0) {
                                set_destroy(setu);
                                return -1;
                        }
                }

                member = list_next(member);
        }

        return 0;
}

int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
        ListElem *member;

        if (set_init(seti, set1->match, NULL) != 0) {
                return -1;
        }

        member = list_head(set1);
        while (member) {
                if (set_is_member(set2, list_data(member))) {
                        if (set_insert(seti, list_data(member)) != 0) {
                                set_destroy(seti);
                                return -1;
                        }
                }

                member = list_next(member);
        }

        return 0;
}

int set_difference(Set *setd, const Set *set1, const Set *set2)
{
        ListElem *member;

        if (set_init(setd, set1->match, NULL) != 0) {
                return -1;
        }

        member = list_head(set1);
        while (member) {
                if (!set_is_member(set2, list_data(member))) {
                        if (set_insert(setd, list_data(member)) != 0) {
                                set_destroy(setd);
                                return -1;
                        }
                }
                member = list_next(member);
        }

        return 0;
}

int set_is_member(const Set *set, const void *data)
{
        ListElem *member;

        member = list_head(set);
        while (member) {
                if (set->match(data, list_data(member))) {
                        return 1;
                }

                member = list_next(member);
        }

        return 0;
}

int set_is_subset(const Set *set1, const Set *set2)
{
        ListElem *member;
        
        if (set_size(set1) > set_size(set2)) {
                return 0;
        }

        member = list_head(set1);
        while (member) {
                if (!set_is_member(set2, list_data(member))) {
                        return 0;
                }
                
                member = list_next(member);
        }

        return 1;
}

int set_is_equal(const Set *set1, const Set *set2)
{
        if (set_size(set1) != set_size(set2)) {
                return 0;
        }

        return set_is_subset(set1, set2);
}
