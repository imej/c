#include <lcthw/DArray.h>
#include <stdio.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
    DArray *rv = calloc(1, sizeof(DArray));
    
    rv->end = 0;
    rv->max = initial_max;
    rv->element_size = element_size;
    rv->expand_rate = DEFAULT_EXPAND_RATE;
    
    void *cnt[rv->max];
    rv->contents = cnt;

    return rv;
}

void DArray_destroy(DArray *array)
{
    if (array != NULL) {
        DArray_free(array);
    }
}

void DArray_clear(DArray *array)
{
    int i;
    if (array != NULL) {
        for (i = 0; i < array->end; i++) {
            free(DArray_remove(array, i));
        }
    }
}

void DArray_clear_destroy(DArray *array)
{
    DArray_clear(array);
    DArray_destroy(array);
}

int DArray_expand(DArray *array)
{
    if (array != NULL) {
        void *cnt[array->max + array->expand_rate];
        memcpy(cnt, array->contents,array->end);
	array->max += array->expand_rate;
    }
    return 0;
}

int DArray_contract(DArray *array)
{
    if (array != NULL) {
        if (array->max > (int)array->expand_rate) {
	    void *cnt[array->max - array->expand_rate];
	    memcpy(cnt, array->contents, (array->max - array->expand_rate));
	    array->max -= array->expand_rate;
	}
    }
    return 0;
}

int DArray_push(DArray *array, void *el)
{
    if (array != NULL && el != NULL) {
        if (array->end + 1 > array->max) {
	    DArray_expand(array);
	}

	void *newelm = DArray_new(array);
	check(newelm != NULL, "DArray_push: cannot allocate memery.");

        memcpy(newelm, el, array->element_size);
	array->contents[array->end + 1] = newelm;
	array->end += 1;
        return 0;
    }
error:
    return 1;
}

void *DArray_pop(DArray *array)
{
    if (array == NULL) {
        return NULL;
    }

    if (array->end == 0) {
        return NULL;
    }

    array->end -= 1;
    void *rv = DArray_remove(array, array->end);

    if (array->max - array->end >= (int)array->expand_rate) {
        DArray_contract(array);
    }
    return rv;
}
/*
int main()
{
    DArray *da = DArray_create(sizeof(int), 10);
    check(da != NULL, "cannot creat DArray.");
    
    //printf("max = %d\n", DArray_max(da));
    //printf("count = %d\n", DArray_count(da));
    //printf("size of contents: %d\n", sizeof(da->contents[100]));
    
    DArray_destroy(da);
    printf("da is destroied.");
error:
    return 1;
}
*/
