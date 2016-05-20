#include "minunit.h"
#include <header.h>
#include <assert.h>

char * test_tree()
{
    struct tnode *p = addtree(NULL, "how", 1);
    p = addtree(p, "how", 3);
    p = addtree(p, "are", 2);
    p = addtree(p, "you", 100);

    treeprint(p);

    tdestroy(p);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_tree);

    return NULL;
}

RUN_TESTS(all_tests);
