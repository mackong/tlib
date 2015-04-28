#include <stdio.h>
#include <stdlib.h>

#include <check.h>

#include "../tlib.h"

static void dump(const void *data)
{
        printf("%d ", data);
}

static int match(const void *key1, const void *key2)
{
        return key1 == key2;
}

static int compare(const void *data1, const void *data2)
{
        if (data1 < data2) {
                return -1;
        } else if (data1 > data2) {
                return 1;
        } else {
                return 0;
        }
}

static int sort_compare(const void *key1, const void *key2)
{
        int tmp1 = *(int *)key1;
        int tmp2 = *(int *)key2;

        if (tmp1 < tmp2) {
                return -1;
        } else if (tmp1 > tmp2) {
                return 1;
        } else {
                return 0;
        }
}

START_TEST (test_list)
{
        List *list = NULL;
        int ret;
        void *data;

        list = (List *)malloc(sizeof(List));
        ck_assert_ptr_ne(list, NULL);

        ret = list_init(list, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(list_size(list), 0);
        ck_assert_ptr_eq(list_head(list), NULL);
        ck_assert_ptr_eq(list_tail(list), NULL);

        list_ins_next(list, NULL, (const void *)1);
        ck_assert_int_eq(list_size(list), 1);
        ck_assert_int_eq(list_data(list_head(list)), 1);
        ck_assert_int_eq(list_data(list_tail(list)), 1);

        list_ins_next(list, list_head(list), (const void *)2);
        ck_assert_int_eq(list_size(list), 2);
        ck_assert_int_eq(list_data(list_head(list)), 1);
        ck_assert_int_eq(list_data(list_tail(list)), 2);

        list_ins_next(list, list_tail(list), (const void *)3);
        ck_assert_int_eq(list_size(list), 3);
        ck_assert_int_eq(list_data(list_head(list)), 1);
        ck_assert_int_eq(list_data(list_tail(list)), 3);
        ck_assert_int_eq(list_data(list_next(list_head(list))), 2);

        ret = list_rem_next(list, NULL, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(data, 1);
        ck_assert_int_eq(list_size(list), 2);
        
        ret = list_rem_next(list, list_head(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(data, 3);
        ck_assert_int_eq(list_size(list), 1);

        ret = list_rem_next(list, NULL, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(data, 2);
        ck_assert_int_eq(list_size(list), 0);
        ck_assert_ptr_eq(list_head(list), NULL);
        ck_assert_ptr_eq(list_tail(list), NULL);

        ret = list_rem_next(list, NULL, (void **)&data);
        ck_assert_int_eq(ret, -1);
        
        ret = list_destroy(list);
        ck_assert_int_eq(ret, 0);
        
	free(list);
}
END_TEST

START_TEST (test_dlist_1)
{
        DList *list = NULL;
        int ret;
        void *data;

        list = (DList *)malloc(sizeof(DList));
        ck_assert_ptr_ne(list, NULL);

        ret = dlist_init(list, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 0);
        ck_assert_ptr_eq(dlist_head(list), NULL);
        ck_assert_ptr_eq(dlist_tail(list), NULL);

        dlist_ins_next(list, NULL, (const void *)1);
        ck_assert_int_eq(dlist_size(list), 1);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 1);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 1);

        dlist_ins_next(list, dlist_head(list), (const void *)2);
        ck_assert_int_eq(dlist_size(list), 2);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 1);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 2);
        ck_assert_int_eq(dlist_data(dlist_next(dlist_head(list))), 2);
        ck_assert_int_eq(dlist_data(dlist_prev(dlist_tail(list))), 1);

        dlist_ins_next(list, dlist_tail(list), (const void *)3);
        ck_assert_int_eq(dlist_size(list), 3);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 1);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 3);
        ck_assert_int_eq(dlist_data(dlist_next(dlist_head(list))), 2);
        ck_assert_int_eq(dlist_data(dlist_prev(dlist_tail(list))), 2);

        ret = dlist_remove(list, dlist_head(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 2);
        ck_assert_int_eq(data, 1);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 2);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 3);

        ret = dlist_remove(list, dlist_tail(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 1);
        ck_assert_int_eq(data, 3);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 2);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 2);

        ret = dlist_remove(list, dlist_head(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 0);
        ck_assert_int_eq(data, 2);
        ck_assert_ptr_eq(dlist_head(list), NULL);
        ck_assert_ptr_eq(dlist_tail(list), NULL);

        ret = dlist_remove(list, dlist_head(list), (void **)&data);
        ck_assert_int_eq(ret, -1);
        
        ret = dlist_destroy(list);
        ck_assert_int_eq(ret, 0);
        
        free(list);
}
END_TEST

START_TEST (test_dlist_2)
{
        DList *list = NULL;
        int ret;
        void *data;

        list = (DList *)malloc(sizeof(DList));
        ck_assert_ptr_ne(list, NULL);

        ret = dlist_init(list, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 0);
        ck_assert_ptr_eq(dlist_head(list), NULL);
        ck_assert_ptr_eq(dlist_tail(list), NULL);

        dlist_ins_prev(list, NULL, (const void *)1);
        ck_assert_int_eq(dlist_size(list), 1);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 1);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 1);

        dlist_ins_prev(list, dlist_head(list), (const void *)2);
        ck_assert_int_eq(dlist_size(list), 2);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 2);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 1);
        ck_assert_int_eq(dlist_data(dlist_next(dlist_head(list))), 1);
        ck_assert_int_eq(dlist_data(dlist_prev(dlist_tail(list))), 2);

        dlist_ins_prev(list, dlist_tail(list), (const void *)3);
        ck_assert_int_eq(dlist_size(list), 3);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 2);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 1);
        ck_assert_int_eq(dlist_data(dlist_next(dlist_head(list))), 3);
        ck_assert_int_eq(dlist_data(dlist_prev(dlist_tail(list))), 3);

        ret = dlist_remove(list, dlist_head(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 2);
        ck_assert_int_eq(data, 2);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 3);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 1);

        ret = dlist_remove(list, dlist_tail(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 1);
        ck_assert_int_eq(data, 1);
        ck_assert_int_eq(dlist_data(dlist_head(list)), 3);
        ck_assert_int_eq(dlist_data(dlist_tail(list)), 3);

        ret = dlist_remove(list, dlist_head(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 0);
        ck_assert_int_eq(data, 3);
        ck_assert_ptr_eq(dlist_head(list), NULL);
        ck_assert_ptr_eq(dlist_tail(list), NULL);

        ret = dlist_remove(list, dlist_head(list), (void **)&data);
        ck_assert_int_eq(ret, -1);
        
        ret = dlist_destroy(list);
        ck_assert_int_eq(ret, 0);
        
        free(list);
}
END_TEST

START_TEST (test_clist)
{
        CList *list = NULL;
        int ret;
        void *data;

        list = (CList *)malloc(sizeof(CList));
        ck_assert_ptr_ne(list, NULL);

        ret = clist_init(list, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(clist_size(list), 0);
        ck_assert_ptr_eq(clist_head(list), NULL);

        clist_ins_next(list, NULL, (const void *)1);
        ck_assert_int_eq(clist_size(list), 1);
        ck_assert_int_eq(clist_data(clist_head(list)), 1);

        clist_ins_next(list, clist_head(list), (const void *)2);
        ck_assert_int_eq(clist_size(list), 2);
        ck_assert_int_eq(clist_data(clist_head(list)), 1);
        ck_assert_int_eq(clist_data(clist_next(clist_head(list))), 2);

        clist_ins_next(list, clist_head(list), (const void *)3);
        ck_assert_int_eq(clist_size(list), 3);
        ck_assert_int_eq(clist_data(clist_head(list)), 1);
        ck_assert_int_eq(clist_data(clist_next(clist_head(list))), 3);
        ck_assert_int_eq(clist_data(clist_next(clist_next(clist_head(list)))), 2);

        ret = clist_rem_next(list, clist_head(list),  (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(clist_size(list), 2);
        ck_assert_int_eq(data, 3);

        ret = clist_rem_next(list, clist_head(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(clist_size(list), 1);
        ck_assert_int_eq(data, 2);

        ret = clist_rem_next(list, clist_head(list), (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(clist_size(list), 0);
        ck_assert_int_eq(data, 1);

        ret = clist_rem_next(list, clist_head(list), (void **)&data);
        ck_assert_int_eq(ret, -1);
        
        ret = clist_destroy(list);
        ck_assert_int_eq(ret, 0);
        
        free(list);
}
END_TEST

START_TEST (test_stack)
{
        Stack *stack = NULL;
        int ret;
        void *data;

        stack = (Stack *)malloc(sizeof(Stack));
        ck_assert_ptr_ne(stack, NULL);

        ret = stack_init(stack, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(stack_size(stack), 0);

        stack_push(stack, (const void *)1);
        ck_assert_int_eq(stack_size(stack), 1);
        ck_assert_int_eq(stack_peek(stack), 1);

        stack_push(stack, (const void *)2);
        ck_assert_int_eq(stack_size(stack), 2);
        ck_assert_int_eq(stack_peek(stack), 2);

        stack_push(stack, (const void *)3);
        ck_assert_int_eq(stack_size(stack), 3);
        ck_assert_int_eq(stack_peek(stack), 3);

        stack_push(stack, (const void *)4);
        ck_assert_int_eq(stack_size(stack), 4);
        ck_assert_int_eq(stack_peek(stack), 4);

        ret = stack_pop(stack, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(data, 4);
        ck_assert_int_eq(stack_size(stack), 3);

        ret = stack_pop(stack, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(data, 3);
        ck_assert_int_eq(stack_size(stack), 2);

        ret = stack_pop(stack, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(data, 2);
        ck_assert_int_eq(stack_size(stack), 1);

        ret = stack_pop(stack, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(data, 1);
        ck_assert_int_eq(stack_size(stack), 0);

        ret = stack_pop(stack, (void **)&data);
        ck_assert_int_eq(ret, -1);
        
        ret = stack_destroy(stack);
        ck_assert_int_eq(ret, 0);
        
        free(stack);
}
END_TEST

START_TEST (test_queue)
{
        Queue *queue;
        int ret;
        void *data;

        queue = (Queue *)malloc(sizeof(Queue));
        ck_assert_ptr_ne(queue, NULL);

        ret = queue_init(queue, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(queue_size(queue), 0);

        queue_enqueue(queue, (const void *)1);
        ck_assert_int_eq(queue_size(queue), 1);
        ck_assert_int_eq(queue_peek(queue), 1);

        queue_enqueue(queue, (const void *)2);
        ck_assert_int_eq(queue_size(queue), 2);
        ck_assert_int_eq(queue_peek(queue), 1);
        
        queue_enqueue(queue, (const void *)3);
        ck_assert_int_eq(queue_size(queue), 3);
        ck_assert_int_eq(queue_peek(queue), 1);

        queue_enqueue(queue, (const void *)4);
        ck_assert_int_eq(queue_size(queue), 4);
        ck_assert_int_eq(queue_peek(queue), 1);

        ret = queue_dequeue(queue, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(queue_size(queue), 3);
        ck_assert_int_eq(data, 1);

        ret = queue_dequeue(queue, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(queue_size(queue), 2);
        ck_assert_int_eq(data, 2);

        ret = queue_dequeue(queue, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(queue_size(queue), 1);
        ck_assert_int_eq(data, 3);

        ret = queue_dequeue(queue, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(queue_size(queue), 0);
        ck_assert_int_eq(data, 4);

        ret = queue_dequeue(queue, (void **)&data);
        ck_assert_int_eq(ret, -1);
        
        ret = queue_destroy(queue);
        ck_assert_int_eq(ret, 0);

        free(queue);
}
END_TEST

START_TEST (test_set)
{
        Set *set;
        int ret;
        void *data;

        set = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set, NULL);

        ret = set_init(set, match, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 0);

        ret = set_insert(set, (const void *)1);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 1);

        ret = set_insert(set, (const void *)2);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 2);

        ret = set_insert(set, (const void *)1);
        ck_assert_int_eq(ret, 1);
        ck_assert_int_eq(set_size(set), 2);

        ret = set_insert(set, (const void *)3);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 3);

        data = (void *)1; /** be careful */
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 2);
        ck_assert_int_eq(data, 1);

        data = (void *)4;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, -1);
        ck_assert_int_eq(set_size(set), 2);
        ck_assert_int_eq(data, 4);

        data = (void *)2;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 1);
        ck_assert_int_eq(data, 2);

        data = (void *)3;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 0);
        ck_assert_int_eq(data, 3);

        data = (void *)1;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, -1);
        ck_assert_int_eq(set_size(set), 0);
        ck_assert_int_eq(data, 1);

        ret = set_destroy(set);
        ck_assert_int_eq(ret, 0);

        free(set);
}
END_TEST

START_TEST (test_set_union)
{
        Set *setu, *set1, *set2;
        int ret;

        set1 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set1, NULL);

        set2 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set2, NULL);

        setu = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(setu, NULL);

        set_init(set1, match, NULL);
        set_init(set2, match, NULL);

        set_insert(set1, (const void *)1);
        set_insert(set1, (const void *)2);
        set_insert(set1, (const void *)3);
        set_insert(set1, (const void *)4);

        set_insert(set2, (const void *)1);
        set_insert(set2, (const void *)3);
        set_insert(set2, (const void *)5);
        set_insert(set2, (const void *)7);

        ret = set_union(setu, set1, set2);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(setu), 6);
        ck_assert(set_is_member(setu, (const void *)1));
        ck_assert(set_is_member(setu, (const void *)2));
        ck_assert(set_is_member(setu, (const void *)3));
        ck_assert(set_is_member(setu, (const void *)4));
        ck_assert(set_is_member(setu, (const void *)5));
        ck_assert(set_is_member(setu, (const void *)7));
        set_destroy(setu);

        set_destroy(set1);
        set_destroy(set2);
        free(set1);
        free(set2);
        free(setu);
}
END_TEST

START_TEST (test_set_intersection)
{
        Set *seti, *set1, *set2;
        int ret;

        set1 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set1, NULL);

        set2 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set2, NULL);

        seti = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(seti, NULL);

        set_init(set1, match, NULL);
        set_init(set2, match, NULL);

        set_insert(set1, (const void *)1);
        set_insert(set1, (const void *)2);
        set_insert(set1, (const void *)3);
        set_insert(set1, (const void *)4);

        set_insert(set2, (const void *)1);
        set_insert(set2, (const void *)3);
        set_insert(set2, (const void *)5);
        set_insert(set2, (const void *)7);

        ret = set_intersection(seti, set1, set2);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(seti), 2);
        ck_assert(set_is_member(seti, (const void *)1));
        ck_assert(!set_is_member(seti, (const void *)2));
        ck_assert(set_is_member(seti, (const void *)3));
        ck_assert(!set_is_member(seti, (const void *)4));
        ck_assert(!set_is_member(seti, (const void *)5));
        ck_assert(!set_is_member(seti, (const void *)7));
        set_destroy(seti);

        set_destroy(set1);
        set_destroy(set2);
        free(set1);
        free(set2);
        free(seti);
}
END_TEST

START_TEST (test_set_difference)
{
        Set *setd, *set1, *set2;
        int ret;

        set1 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set1, NULL);

        set2 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set2, NULL);

        setd = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(setd, NULL);

        set_init(set1, match, NULL);
        set_init(set2, match, NULL);

        set_insert(set1, (const void *)1);
        set_insert(set1, (const void *)2);
        set_insert(set1, (const void *)3);
        set_insert(set1, (const void *)4);

        set_insert(set2, (const void *)1);
        set_insert(set2, (const void *)3);
        set_insert(set2, (const void *)5);
        set_insert(set2, (const void *)7);

        ret = set_difference(setd, set1, set2);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(setd), 2);
        ck_assert(!set_is_member(setd, (const void *)1));
        ck_assert(set_is_member(setd, (const void *)2));
        ck_assert(!set_is_member(setd, (const void *)3));
        ck_assert(set_is_member(setd, (const void *)4));
        ck_assert(!set_is_member(setd, (const void *)5));
        ck_assert(!set_is_member(setd, (const void *)7));
        set_destroy(setd);

        set_destroy(set1);
        set_destroy(set2);
        free(set1);
        free(set2);
        free(setd);
}
END_TEST

START_TEST (test_set_is_member)
{
        Set *set;

        set = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set, NULL);

        set_init(set, match, NULL);

        set_insert(set, (const void *)1);
        set_insert(set, (const void *)2);
        set_insert(set, (const void *)3);
        set_insert(set, (const void *)4);

        ck_assert(set_is_member(set, (const void *)1));
        ck_assert(set_is_member(set, (const void *)2));
        ck_assert(set_is_member(set, (const void *)3));
        ck_assert(set_is_member(set, (const void *)4));
        ck_assert(!set_is_member(set, (const void *)5));
        ck_assert(!set_is_member(set, (const void *)6));
        ck_assert(!set_is_member(set, (const void *)7));

        set_destroy(set);
        free(set);
}
END_TEST

START_TEST (test_set_is_subset)
{
        Set *set1, *set2;
        int *data;

        set1 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set1, NULL);

        set2 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set2, NULL);

        set_init(set1, match, NULL);
        set_init(set2, match, NULL);

        set_insert(set1, (const void *)1);
        set_insert(set1, (const void *)2);
        set_insert(set1, (const void *)3);
        set_insert(set1, (const void *)4);

        set_insert(set2, (const void *)1);
        set_insert(set2, (const void *)3);
        set_insert(set2, (const void *)5);
        set_insert(set2, (const void *)7);

        ck_assert(!set_is_subset(set1, set2));

        data = (int *)4;
        set_remove(set1, (void **)&data);
        ck_assert(!set_is_subset(set1, set2));

        data = (int *)2;
        set_remove(set1, (void **)&data);
        ck_assert(set_is_subset(set1, set2));

        data = (int *)3;
        set_remove(set2, (void **)&data);
        ck_assert(!set_is_subset(set1, set2));
        
        set_destroy(set1);
        set_destroy(set2);
        free(set1);
        free(set2);
}
END_TEST

START_TEST (test_set_is_equal)
{
        Set *set1, *set2;
        int *data;

        set1 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set1, NULL);

        set2 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set2, NULL);

        set_init(set1, match, NULL);
        set_init(set2, match, NULL);

        set_insert(set1, (const void *)1);
        set_insert(set1, (const void *)2);
        set_insert(set1, (const void *)3);
        set_insert(set1, (const void *)4);

        set_insert(set2, (const void *)1);
        set_insert(set2, (const void *)3);
        set_insert(set2, (const void *)5);
        set_insert(set2, (const void *)7);

        ck_assert(!set_is_equal(set1, set2));

        data = (int *)4;
        set_remove(set1, (void **)&data);
        ck_assert(!set_is_equal(set1, set2));

        data = (int *)2;
        set_remove(set1, (void **)&data);
        ck_assert(!set_is_equal(set1, set2));

        data = (int *)5;
        set_remove(set2, (void **)&data);
        ck_assert(!set_is_equal(set1, set2));

        data = (int *)7;
        set_remove(set2, (void **)&data);
        ck_assert(set_is_equal(set1, set2));

        data = (int *)3;
        set_remove(set2, (void **)&data);
        ck_assert(!set_is_equal(set1, set2));
        
        set_destroy(set1);
        set_destroy(set2);
        free(set1);
        free(set2);
}
END_TEST

START_TEST (test_set_cover)
{
        Set *members, *subsets, *cover;
        Set *s1, *s2, *s3, *s4, *s5, *s6, *s7;
        Set *subset;
        Set intersection;
        ListElem *member, *max_member;
        int max_size;
        int *data;
        int ret;

        members = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(members, NULL);

        subsets = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(subsets, NULL);

        cover = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(cover, NULL);

        s1 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(s1, NULL);
        s2 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(s2, NULL);
        s3 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(s3, NULL);
        s4 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(s4, NULL);
        s5 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(s5, NULL);
        s6 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(s6, NULL);
        s7 = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(s7, NULL);

        set_init(members, match, NULL);
        set_init(subsets, match, NULL);
        set_init(cover, match, NULL);
        set_init(s1, match, NULL);
        set_init(s2, match, NULL);
        set_init(s3, match, NULL);
        set_init(s4, match, NULL);
        set_init(s5, match, NULL);
        set_init(s6, match, NULL);
        set_init(s7, match, NULL);

        set_insert(s1, (const void *)1);
        set_insert(s1, (const void *)2);
        set_insert(s1, (const void *)3);
        set_insert(s1, (const void *)4);

        set_insert(s2, (const void *)5);
        set_insert(s2, (const void *)6);
        set_insert(s2, (const void *)7);
        set_insert(s2, (const void *)8);
        set_insert(s2, (const void *)9);

        set_insert(s3, (const void *)10);
        set_insert(s3, (const void *)11);
        set_insert(s3, (const void *)12);

        set_insert(s4, (const void *)1);
        set_insert(s4, (const void *)5);

        set_insert(s5, (const void *)2);
        set_insert(s5, (const void *)6);
        set_insert(s5, (const void *)7);

        set_insert(s6, (const void *)3);
        set_insert(s6, (const void *)4);
        set_insert(s6, (const void *)7);
        set_insert(s6, (const void *)8);
        set_insert(s6, (const void *)11);
        set_insert(s6, (const void *)12);

        set_insert(s7, (const void *)12);

        set_insert(members, (const void *)1);
        set_insert(members, (const void *)2);
        set_insert(members, (const void *)3);
        set_insert(members, (const void *)4);
        set_insert(members, (const void *)5);
        set_insert(members, (const void *)6);
        set_insert(members, (const void *)7);
        set_insert(members, (const void *)8);
        set_insert(members, (const void *)9);
        set_insert(members, (const void *)10);
        set_insert(members, (const void *)11);
        set_insert(members, (const void *)12);

        set_insert(subsets, (const void *)s1);
        set_insert(subsets, (const void *)s2);
        set_insert(subsets, (const void *)s3);
        set_insert(subsets, (const void *)s4);
        set_insert(subsets, (const void *)s5);
        set_insert(subsets, (const void *)s6);
        set_insert(subsets, (const void *)s7);

        while (set_size(members) && set_size(subsets)) {
                max_size = 0;
                member = list_head(subsets);
                while (member) {
                        ret = set_intersection(&intersection, (Set *)list_data(member), members);
                        ck_assert_int_eq(ret, 0);

                        if (set_size(&intersection) > max_size) {
                                max_member = member;
                                max_size = set_size(&intersection);
                        }

                        set_destroy(&intersection);

                        member = list_next(member);
                }

                ck_assert_int_gt(max_size, 0);

                subset = (Set *)list_data(max_member);
                ret = set_insert(cover, subset);
                ck_assert_int_eq(ret, 0);

                member = list_head(subset);
                while (member) {
                        data = list_data(member);
                        ret = set_remove(members, (void **)&data);

                        if (ret == 0 && members->destroy) {
                                members->destroy(data);
                        }

                        member = list_next(member);
                }

                ret = set_remove(subsets, (void **)&subset);
                ck_assert_int_eq(ret, 0);
        }

        ck_assert_int_eq(set_size(members), 0);

        ck_assert_int_eq(set_size(cover), 4);
        ck_assert(set_is_member(cover, (const void *)s6));
        ck_assert(set_is_member(cover, (const void *)s2));
        ck_assert(set_is_member(cover, (const void *)s1));
        ck_assert(set_is_member(cover, (const void *)s3));
        
        
        set_destroy(s1);
        set_destroy(s2);
        set_destroy(s3);
        set_destroy(s4);
        set_destroy(s5);
        set_destroy(s6);
        set_destroy(s7);

        set_destroy(members);
        set_destroy(subsets);
        set_destroy(cover);

        free(s1);
        free(s2);
        free(s3);
        free(s4);
        free(s5);
        free(s6);
        free(s7);

        free(members);
        free(subsets);
        free(cover);
}
END_TEST

START_TEST (test_bistree)
{
        BisTree *tree;
        int ret;
        void *data;

        tree = (BisTree *)malloc(sizeof(BisTree));
        ck_assert_ptr_ne(tree, NULL);

        ret = bistree_init(tree, compare, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 0);

        ret = bistree_insert(tree, (const void *)27);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 1);

        ret = bistree_insert(tree, (const void *)45);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 2);

        ret = bistree_insert(tree, (const void *)34);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 3);

        ret = bistree_insert(tree, (const void *)20);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 4);

        ret = bistree_insert(tree, (const void *)11);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 5);

        ret = bistree_insert(tree, (const void *)59);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 6);

        ret = bistree_insert(tree, (const void *)10);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 7);
        
        ret = bistree_insert(tree, (const void *)25);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 8);

        ret = bistree_insert(tree, (const void *)29);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 9);

        ret = bistree_insert(tree, (const void *)30);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 10);

        bistree_preorder_dump(tree, dump);
        printf("\n");
        bistree_inorder_dump(tree, dump);
        printf("\n");
        bistree_postorder_dump(tree, dump);
        printf("\n");

        data = (void *)5;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, -1);

        data = (void *)100;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, -1);
        
        data = (void *)27;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, 0);

        data = (void *)10;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, 0);

        data = (void *)34;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, 0);
        
        ret = bistree_remove(tree, (const void *)27);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 10);

        ret = bistree_remove(tree, (const void *)34);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 10);

        data = (void *)27;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, -1);

        data = (void *)10;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, 0);

        data = (void *)34;
        ret = bistree_lookup(tree, &data);
        ck_assert_int_eq(ret, -1);
        
        bistree_preorder_dump(tree, dump);
        printf("\n");
        bistree_inorder_dump(tree, dump);
        printf("\n");
        bistree_postorder_dump(tree, dump);
        printf("\n");
        
        ret = bistree_destroy(tree);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(bistree_size(tree), 0);

        free(tree);
}
END_TEST

START_TEST (test_heap)
{
        Heap *heap;
        int ret, i;
        int datas[] = {15, 17, 18, 19, 20, 22, 24, 25};
        void *top;

        heap = (Heap *)malloc(sizeof(Heap));
        ck_assert_ptr_ne(heap, NULL);

        ret = heap_init(heap, compare, NULL);
        ck_assert_int_eq(ret, 0);

        for (i = 0; i < sizeof(datas) / sizeof(datas[0]); i++) {
                ret = heap_insert(heap, (const void *)datas[i]);
                ck_assert_int_eq(ret, 0);
                ck_assert_int_eq(heap_size(heap), i + 1);
        }

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 25);
        ck_assert_int_eq(heap_size(heap), --i);

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 24);
        ck_assert_int_eq(heap_size(heap), --i);

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 22);
        ck_assert_int_eq(heap_size(heap), --i);

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 20);
        ck_assert_int_eq(heap_size(heap), --i);

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 19);
        ck_assert_int_eq(heap_size(heap), --i);

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 18);
        ck_assert_int_eq(heap_size(heap), --i);

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 17);
        ck_assert_int_eq(heap_size(heap), --i);

        ret = heap_extract(heap, &top);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(top, 15);
        ck_assert_int_eq(heap_size(heap), --i);
        
        ret = heap_destroy(heap);
        ck_assert_int_eq(ret, 0);
        
        free(heap);
}
END_TEST

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

START_TEST (test_issort)
{
        int data[] = {23, 21, 76, 16, 52, 43};
        int ret;

        ret = issort(data, ARRAY_SIZE(data), sizeof(data[0]), sort_compare);
        ck_assert_int_eq(ret, 0);

        ck_assert_int_eq(data[0], 16);
        ck_assert_int_eq(data[1], 21);
        ck_assert_int_eq(data[2], 23);
        ck_assert_int_eq(data[3], 43);
        ck_assert_int_eq(data[4], 52);
        ck_assert_int_eq(data[5], 76);
}
END_TEST

START_TEST (test_qksort)
{
        int data[] = {23, 21, 76, 16, 52, 43};
        int ret;

        ret = qksort(data, ARRAY_SIZE(data), sizeof(data[0]), sort_compare);
        ck_assert_int_eq(ret, 0);

        ck_assert_int_eq(data[0], 16);
        ck_assert_int_eq(data[1], 21);
        ck_assert_int_eq(data[2], 23);
        ck_assert_int_eq(data[3], 43);
        ck_assert_int_eq(data[4], 52);
        ck_assert_int_eq(data[5], 76);
}
END_TEST

START_TEST (test_mgsort)
{
        int data[] = {23, 21, 76, 16, 52, 43};
        int ret;

        ret = mgsort(data, ARRAY_SIZE(data), sizeof(data[0]), sort_compare);
        ck_assert_int_eq(ret, 0);

        ck_assert_int_eq(data[0], 16);
        ck_assert_int_eq(data[1], 21);
        ck_assert_int_eq(data[2], 23);
        ck_assert_int_eq(data[3], 43);
        ck_assert_int_eq(data[4], 52);
        ck_assert_int_eq(data[5], 76);
}
END_TEST

START_TEST (test_ctsort)
{
        int data[] = {23, 21, 76, 16, 52, 43};
        int ret;

        ret = ctsort(data, ARRAY_SIZE(data), 76 + 1);
        ck_assert_int_eq(ret, 0);

        ck_assert_int_eq(data[0], 16);
        ck_assert_int_eq(data[1], 21);
        ck_assert_int_eq(data[2], 23);
        ck_assert_int_eq(data[3], 43);
        ck_assert_int_eq(data[4], 52);
        ck_assert_int_eq(data[5], 76);
}
END_TEST

START_TEST (test_rxsort)
{
        int data[] = {23, 21, 76, 16, 52, 43};
        int ret;

        ret = rxsort(data, ARRAY_SIZE(data), 2, 10);
        ck_assert_int_eq(ret, 0);

        ck_assert_int_eq(data[0], 16);
        ck_assert_int_eq(data[1], 21);
        ck_assert_int_eq(data[2], 23);
        ck_assert_int_eq(data[3], 43);
        ck_assert_int_eq(data[4], 52);
        ck_assert_int_eq(data[5], 76);
}
END_TEST

Suite *ds_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Data Structure Suite");

        tc_core = tcase_create("Data Structure Core");

        tcase_add_test(tc_core, test_list);
        tcase_add_test(tc_core, test_dlist_1);
        tcase_add_test(tc_core, test_dlist_2);
        tcase_add_test(tc_core, test_clist);
        tcase_add_test(tc_core, test_stack);
        tcase_add_test(tc_core, test_queue);

        tcase_add_test(tc_core, test_set);
        tcase_add_test(tc_core, test_set_union);
        tcase_add_test(tc_core, test_set_intersection);
        tcase_add_test(tc_core, test_set_difference);
        tcase_add_test(tc_core, test_set_is_member);
        tcase_add_test(tc_core, test_set_is_subset);
        tcase_add_test(tc_core, test_set_is_equal);
        tcase_add_test(tc_core, test_set_cover);

        tcase_add_test(tc_core, test_bistree);
        tcase_add_test(tc_core, test_heap);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite * al_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Algorithm Suite");

        tc_core = tcase_create("Algorithm Core");

        tcase_add_test(tc_core, test_issort);
        tcase_add_test(tc_core, test_qksort);
        tcase_add_test(tc_core, test_mgsort);
        tcase_add_test(tc_core, test_ctsort);
        tcase_add_test(tc_core, test_rxsort);
        
        suite_add_tcase(s, tc_core);

        return s;
}

int main(int argc, char *argv[])
{
        SRunner *sr;
        
        sr = srunner_create(NULL);

        srunner_add_suite(sr, ds_suite());
        srunner_add_suite(sr, al_suite());
        
        srunner_run_all(sr, CK_VERBOSE);

        srunner_free(sr);
        
        return 0;
}
