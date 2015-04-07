#include <stdio.h>
#include <stdlib.h>

#include <check.h>

#include "../list.h"
#include "../dlist.h"
#include "../clist.h"
#include "../stack.h"
#include "../queue.h"
#include "../set.h"


START_TEST (test_list_init)
{
        List *list = NULL;
        int ret = 0;

        list = (List *)malloc(sizeof(List));
        ck_assert_ptr_ne(list, NULL);

        ret = list_init(list, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(list_size(list), 0);
        ck_assert_ptr_eq(list_head(list), NULL);
        ck_assert_ptr_eq(list_tail(list), NULL);

        list_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_list_destroy)
{
        List *list = NULL;
        int ret = 0;

        list = (List *)malloc(sizeof(List));
        ck_assert_ptr_ne(list, NULL);

        list_init(list, NULL);

        ret = list_destroy(list);
        ck_assert_int_eq(ret, 0);

        free(list);
}
END_TEST

START_TEST (test_list_ins_next)
{
        List *list = NULL;

        list = (List *)malloc(sizeof(List));
        ck_assert_ptr_ne(list, NULL);

        list_init(list, NULL);

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

        list_destroy(list);
	free(list);
}
END_TEST

START_TEST (test_list_rem_next)
{
        List *list = NULL;
        int *data = NULL;
        int ret;

        list = (List *)malloc(sizeof(List));
        ck_assert_ptr_ne(list, NULL);

        list_init(list, NULL);

        list_ins_next(list, NULL, (const void *)1);
        list_ins_next(list, list_head(list), (const void *)2);
        list_ins_next(list, list_tail(list), (const void *)3);

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
        
        list_destroy(list);
	free(list);
}
END_TEST

START_TEST (test_dlist_init)
{
        DList *list = NULL;
        int ret = 0;

        list = (DList *)malloc(sizeof(DList));
        ck_assert_ptr_ne(list, NULL);

        ret = dlist_init(list, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(dlist_size(list), 0);
        ck_assert_ptr_eq(dlist_head(list), NULL);
        ck_assert_ptr_eq(dlist_tail(list), NULL);

        dlist_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_dlist_destroy)
{
        DList *list = NULL;
        int ret;

        list = (DList *)malloc(sizeof(DList));
        ck_assert_ptr_ne(list, NULL);

        dlist_init(list, NULL);

        ret = dlist_destroy(list);
        ck_assert_int_eq(ret, 0);

        free(list);
}
END_TEST

START_TEST (test_dlist_ins_next)
{
        DList *list = NULL;

        list = (DList *)malloc(sizeof(DList));
        ck_assert_ptr_ne(list, NULL);

        dlist_init(list, NULL);

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

        dlist_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_dlist_ins_prev)
{
        DList *list = NULL;

        list = (DList *)malloc(sizeof(DList));
        ck_assert_ptr_ne(list, NULL);

        dlist_init(list, NULL);

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

        dlist_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_dlist_remove)
{
        DList *list = NULL;
        int *data = NULL;
        int ret;

        list = (DList *)malloc(sizeof(DList));
        ck_assert_ptr_ne(list, NULL);

        dlist_init(list, NULL);

        dlist_ins_next(list, NULL, (const void *)1);
        dlist_ins_next(list, dlist_head(list), (const void *)2);
        dlist_ins_next(list, dlist_tail(list), (const void *)3);

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
        
        dlist_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_clist_init)
{
        CList *list = NULL;
        int ret = 0;

        list = (CList *)malloc(sizeof(CList));
        ck_assert_ptr_ne(list, NULL);

        ret = clist_init(list, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(clist_size(list), 0);
        ck_assert_ptr_eq(clist_head(list), NULL);

        clist_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_clist_destroy)
{
        CList *list = NULL;
        int ret = 0;

        list = (CList *)malloc(sizeof(CList));
        ck_assert_ptr_ne(list, NULL);

        clist_init(list, NULL);

        ret = clist_destroy(list);
        ck_assert_int_eq(ret, 0);

        free(list);
}
END_TEST

START_TEST (test_clist_ins_next)
{
        CList *list = NULL;

        list = (CList *)malloc(sizeof(CList));
        ck_assert_ptr_ne(list, NULL);

        clist_init(list, NULL);

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

        clist_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_clist_rem_next)
{
        CList *list = NULL;
        int *data = NULL;
        int ret;

        list = (CList *)malloc(sizeof(CList));
        ck_assert_ptr_ne(list, NULL);

        clist_init(list, NULL);

        clist_ins_next(list, NULL, (const void *)1);
        clist_ins_next(list, clist_head(list), (const void *)2);
        clist_ins_next(list, clist_head(list), (const void *)3);
        ck_assert_int_eq(clist_size(list), 3);

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
        
        clist_destroy(list);
        free(list);
}
END_TEST

START_TEST (test_stack_init)
{
        Stack *stack = NULL;
        int ret = 0;

        stack = (Stack *)malloc(sizeof(Stack));
        ck_assert_ptr_ne(stack, NULL);

        ret = stack_init(stack, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(stack_size(stack), 0);

        stack_destroy(stack);
        free(stack);
}
END_TEST

START_TEST (test_stack_destroy)
{
        Stack *stack = NULL;
        int ret = 0;

        stack = (Stack *)malloc(sizeof(Stack));
        ck_assert_ptr_ne(stack, NULL);

        stack_init(stack, NULL);
        
        ret = stack_destroy(stack);
        ck_assert_int_eq(ret, 0);

        free(stack);
}
END_TEST

START_TEST (test_stack_push)
{
        Stack *stack = NULL;

        stack = (Stack *)malloc(sizeof(Stack));
        ck_assert_ptr_ne(stack, NULL);

        stack_init(stack, NULL);

        stack_push(stack, (const void *)1);
        ck_assert_int_eq(stack_size(stack), 1);
        ck_assert_int_eq(stack_peek(stack), 1);

        stack_push(stack, (const void *)2);
        ck_assert_int_eq(stack_size(stack), 2);
        ck_assert_int_eq(stack_peek(stack), 2);

        stack_push(stack, (const void *)3);
        ck_assert_int_eq(stack_size(stack), 3);
        ck_assert_int_eq(stack_peek(stack), 3);

        stack_destroy(stack);
        free(stack);
}
END_TEST

START_TEST (test_stack_pop)
{
        Stack *stack = NULL;
        int *data;
        int ret;

        stack = (Stack *)malloc(sizeof(Stack));
        ck_assert_ptr_ne(stack, NULL);

        stack_init(stack, NULL);
        
        stack_push(stack, (const void *)1);
        stack_push(stack, (const void *)2);
        stack_push(stack, (const void *)3);
        stack_push(stack, (const void *)4);

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

        stack_destroy(stack);
        free(stack);
}
END_TEST

START_TEST (test_queue_init)
{
        Queue *queue;
        int ret;

        queue = (Queue *)malloc(sizeof(Queue));
        ck_assert_ptr_ne(queue, NULL);

        ret = queue_init(queue, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(queue_size(queue), 0);

        queue_destroy(queue);
        free(queue);
}
END_TEST

START_TEST (test_queue_destroy)
{
        Queue *queue;
        int ret;

        queue = (Queue *)malloc(sizeof(Queue));
        ck_assert_ptr_ne(queue, NULL);

        queue_init(queue, NULL);

        ret = queue_destroy(queue);
        ck_assert_int_eq(ret, 0);

        free(queue);
}
END_TEST

START_TEST (test_queue_enqueue)
{
        Queue *queue;

        queue = (Queue *)malloc(sizeof(Queue));
        ck_assert_ptr_ne(queue, NULL);

        queue_init(queue, NULL);

        queue_enqueue(queue, (const void *)1);
        ck_assert_int_eq(queue_size(queue), 1);
        ck_assert_int_eq(queue_peek(queue), 1);

        queue_enqueue(queue, (const void *)2);
        ck_assert_int_eq(queue_size(queue), 2);
        ck_assert_int_eq(queue_peek(queue), 1);
        
        queue_enqueue(queue, (const void *)3);
        ck_assert_int_eq(queue_size(queue), 3);
        ck_assert_int_eq(queue_peek(queue), 1);

        queue_destroy(queue);
        free(queue);
}
END_TEST

START_TEST (test_queue_dequeue)
{
        Queue *queue;
        int *data;
        int ret;

        queue = (Queue *)malloc(sizeof(Queue));
        ck_assert_ptr_ne(queue, NULL);

        queue_init(queue, NULL);

        queue_enqueue(queue, (const void *)1);
        queue_enqueue(queue, (const void *)2);
        queue_enqueue(queue, (const void *)3);
        queue_enqueue(queue, (const void *)4);

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

        queue_destroy(queue);
        free(queue);
}
END_TEST

int set_match(const void *key1, const void *key2)
{
        return key1 == key2;
}

START_TEST (test_set_init)
{
        Set *set;
        int ret;

        set = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set, NULL);

        ret = set_init(set, set_match, NULL);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 0);

        set_destroy(set);
        free(set);
}
END_TEST

START_TEST (test_set_destroy)
{
        Set *set;
        int ret;

        set = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set, NULL);

        set_init(set, set_match, NULL);

        ret = set_destroy(set);
        ck_assert_int_eq(ret, 0);

        free(set);
}
END_TEST

START_TEST (test_set_insert)
{
        Set *set;
        int ret;

        set = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set, NULL);

        set_init(set, set_match, NULL);

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

        set_destroy(set);
        free(set);
}
END_TEST

START_TEST (test_set_remove)
{
        Set *set;
        int *data;
        int ret;

        set = (Set *)malloc(sizeof(Set));
        ck_assert_ptr_ne(set, NULL);

        set_init(set, set_match, NULL);

        set_insert(set, (const void *)1);
        set_insert(set, (const void *)2);
        set_insert(set, (const void *)3);

        data = (int *)1; /** be careful */
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 2);
        ck_assert_int_eq(data, 1);

        data = (int *)4;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, -1);
        ck_assert_int_eq(set_size(set), 2);
        ck_assert_int_eq(data, 4);

        data = (int *)2;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 1);
        ck_assert_int_eq(data, 2);

        data = (int *)3;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(set_size(set), 0);
        ck_assert_int_eq(data, 3);

        data = (int *)1;
        ret = set_remove(set, (void **)&data);
        ck_assert_int_eq(ret, -1);
        ck_assert_int_eq(set_size(set), 0);
        ck_assert_int_eq(data, 1);

        set_destroy(set);
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

        set_init(set1, set_match, NULL);
        set_init(set2, set_match, NULL);

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

        set_init(set1, set_match, NULL);
        set_init(set2, set_match, NULL);

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

        set_init(set1, set_match, NULL);
        set_init(set2, set_match, NULL);

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

        set_init(set, set_match, NULL);

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

        set_init(set1, set_match, NULL);
        set_init(set2, set_match, NULL);

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

        set_init(set1, set_match, NULL);
        set_init(set2, set_match, NULL);

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

        set_init(members, set_match, NULL);
        set_init(subsets, set_match, NULL);
        set_init(cover, set_match, NULL);
        set_init(s1, set_match, NULL);
        set_init(s2, set_match, NULL);
        set_init(s3, set_match, NULL);
        set_init(s4, set_match, NULL);
        set_init(s5, set_match, NULL);
        set_init(s6, set_match, NULL);
        set_init(s7, set_match, NULL);

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

Suite *list_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("List_Suite");

        tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_list_init);
        tcase_add_test(tc_core, test_list_destroy);
        tcase_add_test(tc_core, test_list_ins_next);
        tcase_add_test(tc_core, test_list_rem_next);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *dlist_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("DList_Suite");

        tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_dlist_init);
        tcase_add_test(tc_core, test_dlist_destroy);
        tcase_add_test(tc_core, test_dlist_ins_next);
        tcase_add_test(tc_core, test_dlist_ins_prev);
        tcase_add_test(tc_core, test_dlist_remove);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *clist_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("CList_Suite");

        tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_clist_init);
        tcase_add_test(tc_core, test_clist_destroy);
        tcase_add_test(tc_core, test_clist_ins_next);
        tcase_add_test(tc_core, test_clist_rem_next);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *stack_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Stack_Suite");

        tc_core = tcase_create("Core");
        
        tcase_add_test(tc_core, test_stack_init);
        tcase_add_test(tc_core, test_stack_destroy);
        tcase_add_test(tc_core, test_stack_push);
        tcase_add_test(tc_core, test_stack_pop);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *queue_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Queue_Suite");

        tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_queue_init);
        tcase_add_test(tc_core, test_queue_destroy);
        tcase_add_test(tc_core, test_queue_enqueue);
        tcase_add_test(tc_core, test_queue_dequeue);
        
        suite_add_tcase(s, tc_core);

        return s;
}

Suite *set_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Set_Suite");

        tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_set_init);
        tcase_add_test(tc_core, test_set_destroy);
        tcase_add_test(tc_core, test_set_insert);
        tcase_add_test(tc_core, test_set_remove);
        tcase_add_test(tc_core, test_set_union);
        tcase_add_test(tc_core, test_set_intersection);
        tcase_add_test(tc_core, test_set_difference);
        tcase_add_test(tc_core, test_set_is_member);
        tcase_add_test(tc_core, test_set_is_subset);
        tcase_add_test(tc_core, test_set_is_equal);
        tcase_add_test(tc_core, test_set_cover);
        
        suite_add_tcase(s, tc_core);

        return s;
}

int main(int argc, char *argv[])
{
        SRunner *sr;
        
        sr = srunner_create(NULL);

        srunner_add_suite(sr, list_suite());
        srunner_add_suite(sr, dlist_suite());
        srunner_add_suite(sr, clist_suite());
        srunner_add_suite(sr, stack_suite());
        srunner_add_suite(sr, queue_suite());
        srunner_add_suite(sr, set_suite());
        
        srunner_run_all(sr, CK_VERBOSE);

        srunner_free(sr);
        
        return 0;
}
