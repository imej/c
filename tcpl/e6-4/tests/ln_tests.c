#include "minunit.h"
#include <header.h>
#include <assert.h>

char * test_addlnode()
{
    int i;
    struct lnode *p = NULL;
    struct lnode *q = NULL;

    for (i = 100; i < 105; i++) {
        addlnode(p, i);
    }

    q = p;
    while (q != NULL) {
        mu_assert(q->ln == (--i), "q->ln != (--i)");
    }

    destroy_all_lnode(p);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_addlnode);

    return NULL;
}

RUN_TESTS(all_tests);
