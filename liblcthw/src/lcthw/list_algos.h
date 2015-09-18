#ifndef lcthw_List_Algos_h
#define lcthw_List_Algos_h

typedef int (*List_compare)(void *, void *);
int List_bubble_sort(List *list, List_compare);
List *List_merge_sort(List *list, List_compare);
List *merge(List *left, List *right, List_compare);

#endif    

