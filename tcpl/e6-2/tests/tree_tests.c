#include "minunit.h"
#include <tree.h>
#include <assert.h>

char *test_tree()
{
    struct tnode *tree = NULL;
    struct tnode *root = NULL;

    tree = addtree(tree, "I");
    mu_assert(tree != NULL, "Failed to add \"I\" to tree.");
    root = tree;

    tree = addtree(tree, "hate");
    mu_assert(tree != NULL, "Failed to add \"hate\" to tree.");
    
    tree = addtree(tree, "whole wheet");
    mu_assert(tree != NULL, "Failed to add \"whole wheet\" to tree.");

    //treeprint(root);
    tdestroy(root);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_tree);

    return NULL;
}

RUN_TESTS(all_tests);
