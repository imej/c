#include "minunit.h"
#include <nlist.h>
#include <assert.h>

char * test_nlist()
{
    unsigned ui;
    struct nlist *nl;
/*
    ui = hash("how");
    printf("how -> %u\n", ui);

    ui = hash("are");
    printf("are -> %u\n", ui);

    ui = hash("you");
    printf("you -> %u\n", ui);
*/
    nl = install("how", "how");
    nl = install("are", "are");
    nl = install("you", "you");

    nl = lookup("how");
    mu_assert(nl != NULL, "did not find 'how'");
    mu_assert(strcmp(nl->name, "how") == 0, "name is not 'how'");
    mu_assert(strcmp(nl->defn, "how") == 0, "defn is not 'how'");

    undef("how");
    nl = lookup("how");
    mu_assert(nl == NULL, "still find 'how'");

    releaselist();

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_nlist);

    return NULL;
}

RUN_TESTS(all_tests);
