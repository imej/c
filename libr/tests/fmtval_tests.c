/* test standard locale.h */
#include "lr/locale.h"
#include <stdio.h>
#include "minunit.h"

char *test__Fmtval()
{
    // struct lconv *p = localeconv();

    // mu_assert(p != NULL, "localeconv returns NULL.");
    
    char *mynum = malloc(100);
    if (mynum != NULL) {
        _Fmtval(mynum, 39201.456, -2);
    }

    printf("My international money is: %s\n", mynum);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test__Fmtval);
    
    return NULL;
}

RUN_TESTS(all_tests)
