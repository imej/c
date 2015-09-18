#ifndef lcthw_List_Algos_h
#define lcthw_List_Algos_h

#include <lcthw/list.h>

typedef int (*List_compare)(void *, void *);
int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif    

