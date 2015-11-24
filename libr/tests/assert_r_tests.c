#include "minunit.h"
#include "assert_r.h"

char *test_assert_r()
{
    assert_r(1 == 2);   
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_assert_r);
    
    return NULL;
}

RUN_TESTS(all_tests)
