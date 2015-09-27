#ifndef _DArray_h
#define _DArray_h

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

// structure of a dynamic array
typedef struct DArray {
    int end;              // count of elements
    int max;              // maximum elements can hold before next expand
    size_t element_size;  // size of the elements
    size_t expand_rate;   // increase by
    void **contents;      // elements
} DArray;

// create a new dynamic array
DArray *DArray_create(size_t element_size, size_t initial_max);

// release contents and the dynamic array
void DArray_destroy(DArray *array);

// empty contents
void DArray_clear(DArray *array);

// increase the size of contents
int DArray_expand(DArray *array);

// decrease the size of contents. when?
int DArray_contract(DArray *array);

// append a new element to the end of the array
int DArray_push(DArray *array, void *el);

// remove the last element from the array, and return it
void *DArray_pop(DArray *array);

// clear + destroy
void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 3

static inline void DArray_set(DArray *array, int i, void *el)
{
    check(i < array->max, "darray attempt to set past max.");
    if (i > array->end) array->end = i;
    array->contents[i] = el;
error:
    return;
}

static inline void *DArray_get(DArray *array, int i)
{
    check(i < array->max, "darray attempt to get past max.");
    return array->contents[i];
error:
    return NULL;
}

static inline void *DArray_remove(DArray *array, int i)
{
    void *el = array->contents[i];

    array->contents[i] = NULL;

    return el;
}

static inline void *DArray_new(DArray *array)
{
    check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");
    return calloc(1, array->element_size);

error:
    return NULL;
}

#define DArray_free(E) free((E))

#endif
