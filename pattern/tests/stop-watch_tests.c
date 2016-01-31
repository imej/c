#include "stop-watch.h"
#include <stdio.h>
#include "minunit.h"

char *test_enum()
{
    /* I never used enum in C before. 
       Just want to make sure it works as what I expect. */

    return NULL;
}

char *all_tests()
{
    mu_suite_start(); 

    mu_run_test(test_enum);

    return NULL;
}

RUN_TESTS(all_tests)
