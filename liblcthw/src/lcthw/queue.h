#ifndef _queue_h
#define _queue_h

#include <lcthw/list.h>

typedef List Queue;
#define Queue_create() List_create()
#define Queue_destroy(A) List_destroy(A)
#define Queue_send(A, B) List_push(A, B)
#define Queue_recv(A) List_shift(A)
#define Queue_peek(A) List_last(A)
#define Queue_count(A) List_count(A)
#define QUEUE_FOREACH(L, V) LIST_FOREACH(L, first, next, V)
#endif
