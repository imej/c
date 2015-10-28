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

    return NULL;
}

char *test_get_set()
{
/*
    int key[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int data[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int i, rc;
    
    for (i = 0; i < 9; i++) {
        rc = BSTree_set(map, &key[i], &data[i]);
        mu_assert(rc == 0, "Failed to add a value to BSTree.");
    }
*/
    int *key0 = calloc(1, sizeof(int));
    int *data0 = calloc(1, sizeof(int));
    *key0 = 8;
    *data0 = 8;
    int rc = BSTree_set(map, key0, data0);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key1 = calloc(1, sizeof(int));
    int *data1 = calloc(1, sizeof(int));
    *key1 = 3;
    *data1 = 3;
    rc = BSTree_set(map, key1, data1);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key2 = calloc(1, sizeof(int));
    int *data2 = calloc(1, sizeof(int));
    *key2 = 1;
    *data2 = 1;
    rc = BSTree_set(map, key2, data2);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key3 = calloc(1, sizeof(int));
    int *data3 = calloc(1, sizeof(int));
    *key3 = 6;
    *data3 = 6;
    rc = BSTree_set(map, key3, data3);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key4 = calloc(1, sizeof(int));
    int *data4 = calloc(1, sizeof(int));
    *key4 = 4;
    *data4 = 4;
    rc = BSTree_set(map, key4, data4);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key5 = calloc(1, sizeof(int));
    int *data5 = calloc(1, sizeof(int));
    *key5 = 7;
    *data5 = 7;
    rc = BSTree_set(map, key5, data5);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key6 = calloc(1, sizeof(int));
    int *data6 = calloc(1, sizeof(int));
    *key6 = 10;
    *data6 = 10;
    rc = BSTree_set(map, key6, data6);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key7 = calloc(1, sizeof(int));
    int *data7 = calloc(1, sizeof(int));
    *key7 = 14;
    *data7 = 14;
    rc = BSTree_set(map, key7, data7);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    int *key8 = calloc(1, sizeof(int));
    int *data8 = calloc(1, sizeof(int));
    *key8 = 13;
    *data8 = 13;
    rc = BSTree_set(map, key8, data8);    
    mu_assert(rc == 0, "Failed to add a value to BSTree.");

    void *ip = BSTree_get(map, key3);
    mu_assert(ip != NULL, "Failed to get from BSTree");
    mu_assert(*(int *)ip == 6, "Failed to get the correct data from BSTree");

    ip = BSTree_get(map, key8);
    mu_assert(ip != NULL, "Failed to get from BSTree");
    mu_assert(*(int *)ip == 13, "Failed to get the correct data from BSTree");

    return NULL;
}

char *test_delete()
{
    int map_count = map->count;

    int *key = calloc(1, sizeof(int));
    *key = 1;
    void *ip = BSTree_delete(map, key);
    
    mu_assert(map_count -1 == map->count, "Should have one less element.");
    mu_assert(ip != NULL, "Should return something.");
    mu_assert(*(int *)ip == 1, "Should return the deleted data");
    free(key);
    free(ip);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
