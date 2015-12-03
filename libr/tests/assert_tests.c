#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

#ifndef NDEBUG
    #define NDEBUG
#endif
#include "lr/assert.h"

/* staic data */
static int val = 0;

static void field_abort(int sig)
{
    /* handle SIGABRT */
    val++;
    exit(EXIT_SUCCESS);
}

char *test_with_NDEBUG()
{
    /* as NDEBUG is defined, the asserts in this funtion should not work. */
    int i = 0;

    assert(i == 0);
    mu_assert(val == 0, "test_with_NDEBUG 1: val != 0.");

    assert(i > 0);
    mu_assert(val == 0, "test_with_NDEBUG 2: val != 0.");

    return NULL;
}

#ifdef NDEBUG
    #undef NDEBUG
#endif
#include "lr/assert.h"

char *test_without_NDEBUG()
{
    /* we are under the line that undefine NDEBUG, assert should work now. */
    int i = 0;
    assert(signal(SIGABRT, &field_abort) != SIG_ERR);

    assert(i == 0);
    mu_assert(val == 0, "test_without_NDEBUG 1: val != 0.");

    assert(i > 0);
    mu_assert(val > 0, "test_without_NDEBUG 2: val != 0.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_with_NDEBUG);
    mu_run_test(test_without_NDEBUG);
    
    return NULL;
}

RUN_TESTS(all_tests)
