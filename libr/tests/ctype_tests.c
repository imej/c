/* test ctype functions and macros */
#include "lr/assert.h"
#include "lr/ctype.h"
#include "minunit.h"
#include <limits.h>  // UCHAR_MAX
#include <stdio.h>   // puts

char *test_isalnum()
{
    mu_assert(isalnum('1'), "'1' not in isalnum.");
    mu_assert(isalnum('0'), "'0' not in isalnum.");
    mu_assert(isalnum('Y'), "'Y' not in isalnum.");
    mu_assert(isalnum('u'), "'u' not in isalnum.");
    mu_assert(!isalnum(' '), "' ' in isalnum.");

    return NULL;
}

char *test_isalpha()
{
    mu_assert(!isalpha('1'), "'1' in isalpha.");
    mu_assert(!isalpha('0'), "'0' in isalpha.");
    mu_assert(isalpha('Y'), "'Y' not in isalpha.");
    mu_assert(isalpha('u'), "'u' not in isalpha.");
    mu_assert(!isalpha(' '), "' ' in isalpha.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_isalnum);
    mu_run_test(test_isalpha);

    return NULL;
}

RUN_TESTS(all_tests)
