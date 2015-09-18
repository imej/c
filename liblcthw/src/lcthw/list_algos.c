#include <lcthw/dbg.h>
#include <lcthw/list_algos.h>
#include <stdio.h>

int List_bubble_sort(List *list, List_compare cmp)
{
    check(list, "List is NULL");
    check(cmp, "List_compare is NULL");

    if(list->first == NULL) {
        // empty list
	return 0;
    }
    int swapped = 0;
    ListNode *tmpNode;

    do{
        swapped = 0;
        LIST_FOREACH(list, first, next, cur){
	    if(cur->next != NULL && cmp(cur->value, cur->next->value) > 0){
	        tmpNode = cur->next;

	        if(cur->prev != NULL){
		    cur->prev->next = tmpNode;
		} else {
		    // cur is the first element
		    list->first = tmpNode;
		}

		tmpNode->prev = cur->prev;

		if(tmpNode->next != NULL) {
		    tmpNode->next->prev = cur;
		} else {
		    // tmpNode is the last element
		    list->last = cur;
		}

		cur->next = tmpNode->next;
		cur->prev = tmpNode;
                tmpNode->next = cur;

		cur = tmpNode;
		swapped = 1;
	    }
	}
    } while (swapped);
    return 0;

error:
    return 1;
}

inline List *merge(List *left, List *right, List_compare cmp)
{
    check(left, "left is NULL");
    check(right, "right is NULL");
    check(cmp, "List_compare is NULL");

    if(left->first == NULL || right->first == NULL) {
        // empty list
	return NULL;
    }

    List *rv = List_create();
    
    ListNode *ltmp = left->first;
    ListNode *rtmp = right->first;

    while(ltmp != NULL && rtmp != NULL) {
        if(cmp(ltmp->value, rtmp->value) < 0){
	    List_push(rv, ltmp->value);
	    ltmp = ltmp->next;
	} else {
	    List_push(rv, rtmp->value);
	    rtmp = rtmp->next;
	}
    }

    while (ltmp != NULL) {
	List_push(rv, ltmp->value);
	ltmp = ltmp->next;
    }
    while (rtmp != NULL) {
	List_push(rv, rtmp->value);
	rtmp = rtmp->next;
    }
    
    return rv;
error:
    return NULL;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    check(list, "List is NULL");
    check(cmp, "List_compare is NULL");

    if(list->first == NULL) {
        // empty list
	return NULL;
    } 
    
    List *left = List_create();
    List *right = List_create();
    int middle = (int)(List_count(list)/2);
    int mycount = 0;
    ListNode *tmpNode = list->first;

    while(mycount < middle){
        List_push(left, tmpNode->value);
	tmpNode = tmpNode->next;
	mycount++;
    }

    while(mycount < List_count(list)){
        List_push(right, tmpNode->value);
	tmpNode = tmpNode->next;
	mycount++;
    }

    // release resources
    // List_destroy(list);

    if (List_count(left) > 1) {
        left = List_merge_sort(left, cmp);
    }

    if (List_count(right) > 1) {
        right = List_merge_sort(right, cmp);
    }
   
    list =  merge(left, right, cmp);
    
    List_destroy(left);
    List_destroy(right);

    return list;

error:
    return NULL;
}

