#ifndef lcthw_List_Algos_h
#define lcthw_List_Algos_h

typedef int (*List_compare)(void *, void *);
int List_bubble_sort(List *list, List_compare);
int List_merge_sort(List *list, List_compare);

#endif    

