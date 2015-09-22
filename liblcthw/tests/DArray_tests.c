#include "minunit.h"
#include <lcthw/DArray.h>
#include <assert.h>
#include <string.h>

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5
DArray *words;

void test_DArray_create()
{
    words = DArray_create(50 * sizof(char), 5);
    mu_assert(words != NULL, "DArray_create failed.");
}

void test_DArray_push()
{
    int i = 0;

    // push 5 elements into the DArray
    for(i = 0; i < NUM_VALUES; i++) {
        DArray_push(words, values[i]);
    }

    mu_assert(words->end == 4, "DArray_push failed.");
}

void test_DArray_get()
{
    int i = 0;
    void *tmp;

    for (i = 0; i < 5; i++) {
        tmp = DArray_get(words, i);
	mu_assert(strcmp(tmp, values[i]), "DArray_get failed.")
    }
}

void test_DArray_destroy(){
    DArray_clear_destroy(words);
    mu_assert(words != NULL, "DArray_clear_destroy failed");
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_DArray_create);
    mu_run_test(test_DArray_push);
    mu_run_test(test_DArray_get);
    mu_run_test(test_DArray_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
