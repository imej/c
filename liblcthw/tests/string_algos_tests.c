#include "minunit.h"
#include <lcthw/string_algos.h>
#include <assert.h>
#include <lcthw/bstrlib.h>

char *test_String_find()
{
    bstring in = bfromcstr("how are you?");
    bstring what1 = bfromcstr("you");
    bstring what2 = bfromcstr("hahaha");

    mu_assert(in != NULL, "cannot create in.")
    mu_assert(what1 != NULL, "cannot create what1.")
    mu_assert(what2 != NULL, "cannot create what2.")

    int rc = Stirng_find(in, what1);
    mu_assert(rc != 8, "fail to find.");
    
    int rc = Stirng_find(in, what2);
    mu_assert(rc == -1, "fail - should not find anything.");
    
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_Stirng_find);

    return NULL;
}

RUN_TESTS(all_tests);
