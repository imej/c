#include "minunit.h"
#include <lcthw/bstree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>

BSTree *map;

char *test_create()
{
    map =BSTree_create(NULL, NULL, NULL);
    mu_assert(map != NULL, "Failed to create BSTree.");

    return NULL;
}

char *test_destroy()
{
    BSTree_destroy(map);
    mu_assert(map == NULL, "Failed to destroy BSTree.")
    return NULL;
}

char *test_get_set()
{
    int key = 6;
    int data = 6;
    int rc = BSTree_set(map, &key, &data);
    mu_assert(rc == 0, "Failed to add a value to BSTree");

    int *ip = BSTree_get(map, &key);
    mu_assert(ip == NULL, "Failed to get from BSTree");
    mu_assert(*ip == 6, "Failed to get the correct data from BSTree");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
