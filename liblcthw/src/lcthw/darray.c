#include <lcthw/darray.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
    DArray *array = malloc(sizeof(struct DArray));
    check(array != NULL, "Cannot allocate memery for DArray.");

    array->end = 0;
    array->max = initial_max;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;
    array->contents = calloc(initial_max, sizeof(void *));

    return array;
error:
    return NULL;
}

void DArray_destroy(DArray *array)
{
    int i = 0;

    if (array != NULL) {
        for (i = 0; i < array->end + 1; i++) {
	    check(array->contents[i] == NULL, "Can only destroy an empty DArray.");
	}

        if (array->contents != NULL) {
	    free(array->contents);
	}

	free(array);
    }
error:
   i = 1; 
}

void DArray_clear(DArray *array)
{
    if (array != NULL) {
        while (array->end > -1) {
	    if (array->contents[array->end] != NULL) {
	        free(array->contents[array->end]);
	        array->contents[array->end] = NULL;	
	    }
	    --array->end;
	}
    }
}

int DArray_expand(DArray *array)
{
    void **tmp;
    int i = 0;

    if (array != NULL) {
        tmp = calloc(array->max + array->expand_rate, sizeof(void *));
	memcpy(tmp, array->contents, array->max * sizeof(void *));
        array->max += array->expand_rate;

	//for (i = 0; i < array->end + 1; i++) {
	//    free(array->contents[i]);
	//}

	free(array->contents);

	array->contents = tmp;

	return array->max;
    }

    return 0;
}

int DArray_contract(DArray *array)
{
    int i = 0;
    void **tmp;

    if (array != NULL) {
        if ((unsigned int)(array->max - array->end - 1) > array->expand_rate) {
	    tmp = calloc(array->max - array->expand_rate, sizeof(void *));
	    memcpy(tmp, array->contents, (array->max - array->expand_rate) * sizeof(void *));
	    
	    //for (i = 0; i < array->end + 1; i++) {
            //    if (array->contents[i] != NULL) {
	    //        free(array->contents[i]);
            //    }
	    //}

	    free(array->contents);
	    array->contents = tmp;

            array->max -= array->expand_rate;
	    if (array->end > array->max - 1) {
	        array->end = array->max - 1;
	    }
	}

	return array->max;
    }

    return 0;
}

int DArray_push(DArray *array, void *el)
{
    if (array != NULL && el != NULL) {
        if (array->end + 1 == array->max) {
	    DArray_expand(array);
	}

	array->end++;
	DArray_set(array, array->end, el);
    }
}

void *DArray_pop(DArray *array) 
{
    void * rc = NULL;

    if (array != NULL && array->end > 0) {
        rc = DArray_remove(array, array->end);
        array->end -= 1; 
	if ((unsigned int)(array->max - array->end) > array->expand_rate) {
	    DArray_contract(array);
	}
    }

    return rc;
}

void DArray_clear_destroy(DArray *array)
{
    DArray_clear(array);
    DArray_destroy(array);
}
