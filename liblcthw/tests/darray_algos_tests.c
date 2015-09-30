#include "minunit.h"
#include <lcthw/darray.h>
#include <lcthw/darray_algos.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

/**
 * Test with integers
 */
int int_array[] = {1974, 11, 28, 1999, 1, 22};

DArray *create_ints()
{
    unsigned int i = 0;
    int *cp = NULL;

    DArray *ints = DArray_create(sizeof(int *), 100);

    for (i = 0; i < 6; i++) {
        cp = DArray_new(ints);
	*cp = int_array[i];
	DArray_push(ints, cp);
    }

    return ints;
    
}

int cint_cmp(const void *a, const void *b)
{
    const int **ia = (const int **)a;
    const int **ib = (const int **)b;

    return **ia - **ib;
}

int int_is_sorted(DArray *ints)
{
    assert(ints != NULL);
    int i = 0;
    for (i = 0; i < DArray_count(ints) - 1; i++) {
        if (ints->contents[i] && ints->contents[i+1] && cint_cmp(&ints->contents[i], &ints->contents[i+1])>0) {
	    debug("%d %d", *(int *)ints->contents[i], *(int *)ints->contents[i+1]);
	    return 0;
	}
    }

    return 1;
}

char *test_int_qsort()
{
    DArray *ints = create_ints();

    int rc = DArray_qsort(ints, (DArray_compare)cint_cmp);
    mu_assert(int_is_sorted(ints), "ints are not sorted after quick sort.");

    return NULL;
}

/**
 * Test with strings
 */
char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5

DArray *create_words()
{
    int i = 0;
    char *cp = NULL;

    DArray *words = DArray_create(sizeof(char *), 100);

    for(i = 0; i < NUM_VALUES; i++) {
        cp = DArray_new(words);
	*cp = values[i];
        DArray_push(words, cp);
    }

    return words;
}

int cstring_cmp(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

int is_sorted(DArray *words)
{
    assert(words != NULL);
    int i = 0;
    for (i = 0; i < DArray_count(words) - 1; i++) {
        if (words->contents[i] && words->contents[i+1] && cstring_cmp(&words->contents[i], &words->contents[i+1]) > 0) {
	    debug("%s %s", (char *)words->contents[i], (char *)words->contents[i+1]);
	    return 0;
	}
    }

    return 1;
}

char *test_qsort()
{
    DArray *words = create_words();

    // should work on a DArray that needs sorting
    int rc = DArray_qsort(words, (DArray_compare)cstring_cmp);
    mu_assert(rc == 0, "Quick sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after quick sort.");

    // should work on an already sorted DArray
    rc = DArray_qsort(words, (DArray_compare)cstring_cmp);
    mu_assert(rc == 0, "Quick sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already sorted.");

    DArray_clear_destroy(words);

    // should work on an empty list
    words = DArray_create(sizeof(char *), NUM_VALUES);
    rc = DArray_qsort(words, (DArray_compare)cstring_cmp);
    mu_assert(rc == 0, "Quick sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    DArray_clear_destroy(words);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_qsort);
    mu_run_test(test_int_qsort);

    return NULL;
}

RUN_TESTS(all_tests);
