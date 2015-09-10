#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <assert.h>

List *List_create()
{
    struct List *list = malloc(sizeof(struct List));
    
    assert(list != NULL);
    list->count = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void List_push(List *list, void *value)
{
    assert(list != NULL);
    assert(value != NULL);

    // create a ListNode for value
    struct ListNode *ln = malloc(sizeof(struct ListNode));
    assert(ln != NULL);

    ln->value = value;
    
    // add to list
    if (list->count > 0) {
	ln->prev = list->last;
	ln->next = NULL;
	list->last->next = ln;
	list->last = ln;
    } else {
        list->first = ln;
        list->last = ln;
	ln->prev = NULL;
	ln->next = NULL;
    }

    list->count += 1;
}

void *List_pop(List *list)
{
    assert(list != NULL);

    void *value;

    if (list->count > 0) {
        value = list->last->value;
    } else {
        return NULL;
    }

    struct ListNode *lastNode = list->last;
    if (lastNode->prev == NULL) {
        // only one node left
	list->first = NULL;
	list->last = NULL;
    } else {
        struct ListNode *newLast = lastNode->prev;
        lastNode->prev = NULL;
        newLast->next = NULL;
        list->last = newLast;
    }
    list->count -= 1;
    free(lastNode);

    return value;
}

void List_clear(List *list)
{
    struct ListNode *tmpLN;

    assert(list != NULL);
    while (list->first != NULL) {
        tmpLN = list->first;
	list->first = tmpLN.next;
	tmpLN->next = NULL;
	list->first->prev = NULL;
    }
}

int main() 
{
    struct List *list = List_create();
    char *myStr = "good";
    
    List_push(list, myStr);

    printf("list->count = %d\n", list->count);

    List_pop(list);

    printf("list->count = %d\n", list->count);
    return 1;
}
