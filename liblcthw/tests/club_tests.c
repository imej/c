#include "minunit.h"
#include <lcthw/club.h>
#include <assert.h>

char *test_init()
{
    init();

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_init);

    return NULL;
}

// RUN_TESTS(all_tests);
