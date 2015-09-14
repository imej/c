#include <stdio.h>
#include <lcthw/list.h>
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

    if (!(list->count > 0)) {
        // empty list, return NULL
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
    value = lastNode->value;
    free(lastNode);

    return value;
}

void List_clear(List *list)
{
    struct ListNode *tmpLN;

    assert(list != NULL);
    while (list->first != NULL) {
        // disconnect the first element
	tmpLN = list->first;
	list->first = tmpLN->next;
	tmpLN->next = NULL;
	if (list->first != NULL) {
	    list->first->prev = NULL;
	}
        
	// distroy the old first element
	free(tmpLN);
	list->count -= 1;
    }
}

void List_destroy(List *list) 
{
    assert(list != NULL);

    if (list->count > 0) {
        // not empty
	printf("List_destroy: We only can destroy an empty list.");
    } else {
        free(list);
    }
}

void List_clear_destroy(List *list) 
{
    List_clear(list);
    List_destroy(list);
}

void *List_remove(List *list, ListNode *node)
{
    assert(list != NULL);
    assert(node != NULL);

    struct ListNode *prevNode;
    struct ListNode *nextNode;
    void *value = NULL;

    if (node->next == NULL) {
        // last element of the list, pop
	value = List_pop(list);
    } else {
        if (node->prev == NULL) {
	    // first element
            nextNode = node->next;
	    
	    list->first = nextNode;
            nextNode->prev = NULL;
	    node->next = NULL;
	} else {
	    // in the middle of the list
            prevNode = node->prev;
	    nextNode = node->next;

	    prevNode->next = nextNode;
	    nextNode->prev = prevNode;
	    node->prev = NULL;
	    node->next = NULL;
	}
	
	value = node->value;
	free(node);
    }
    return value;
}

int main() 
{
    struct List *list = List_create();
    struct ListNode *ln, *tmp;

    List_push(list, "Toronto");
    List_push(list, "Edmonton");
    List_push(list, "Vancouver");
    List_push(list, "Calgory");
    List_push(list, "St. Albert");
    List_push(list, "Ottawa");
    List_push(list, "Montreal");
    List_push(list, "Quebec");
    List_push(list, "Halifax");
    
    printf("list->count = %d\n", List_count(list));
    printf("first item: %s\n", (char *)List_first(list));
    printf("last item: %s\n", (char *)List_last(list));
    
    printf("\nStart each: -----------------\n");
    LIST_FOREACH(list, first, next, tmp, ln)
    printf("++>%s\n", (char *)ln->value);
    printf("\nEnd each: -----------------\n");

    List_pop(list);

    printf("list->count = %d\n", List_count(list));

    printf("\nStart each: -----------------\n");
    LIST_FOREACH(list, first, next, tmp, ln)
    printf("++>%s\n", (char *)ln->value);
    printf("\nEnd each: -----------------\n");

    printf("Clear & Destroy list.");
    List_clear_destroy(list);

    printf("\nStart each: -----------------\n");
    LIST_FOREACH(list, first, next, tmp, ln)
    printf("++>%s\n", (char *)ln->value);
    printf("\nEnd each: -----------------\n");

    return 1;
}
