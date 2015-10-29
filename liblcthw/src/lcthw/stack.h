#ifndef _stack_h
#define _stack_h

#include <lcthw/list.h>

typedef List Stack;
#define Stack_create() List_create()
#define Stack_destroy(A) List_destroy(A)
#endif
