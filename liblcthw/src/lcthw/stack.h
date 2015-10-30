#ifndef _stack_h
#define _stack_h

#include <lcthw/list.h>

typedef List Stack;
#define Stack_create() List_create()
#define Stack_destroy(A) List_destroy(A)
#define Stack_push(A, B) List_push(A, B)
#define Stack_pop(A) List_pop(A)
#define Stack_peek(A) List_last(A)
#define Stack_count(A) List_count(A)
#define STACK_FOREACH(L, V) LIST_FOREACH(L, first, next, V)
#endif
