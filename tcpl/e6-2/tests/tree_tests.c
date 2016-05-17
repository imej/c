#include "minunit.h"
#include <header.h>
#include <assert.h>

char *test_rmvCmmts()
{
    char line[] = "this is /* a test";
    int inCmmts = 0;

    rmvCmmts(line, &inCmmts);
    mu_assert(strcmp(line, "this is ") == 0, "line is not \'this is \'");
    mu_assert(inCmmts == 1, "inCmmts is not reset to 1");

    char ln1[] = "this /* is a */ test";
    inCmmts = 0;
    rmvCmmts(ln1, &inCmmts);
    mu_assert(strcmp(ln1, "this  test") == 0, "ln1 is not \'this  test\'");
    mu_assert(inCmmts == 0, "inCmmts is not reset to 0");

    char ln2[] = "th*/is /* is a */ test";
    inCmmts = 1;
    rmvCmmts(ln2, &inCmmts);
    mu_assert(strcmp(ln2, "is  test") == 0, "ln2 is not \'is  test\'");
    mu_assert(inCmmts == 0, "inCmmts is not reset to 0");

    char ln3[] = "th*/is /* is a test";
    inCmmts = 1;
    rmvCmmts(ln3, &inCmmts);
    mu_assert(strcmp(ln3, "is ") == 0, "ln3 is not \'is \'");
    mu_assert(inCmmts == 1, "inCmmts is not reset to 0");

    char ln4[] = "this is a test";
    inCmmts = 0;
    rmvCmmts(ln4, &inCmmts);
    mu_assert(strcmp(ln4, "this is a test") == 0, "ln4 is not \'this is a test\'");
    mu_assert(inCmmts == 0, "inCmmts is not reset to 0");

    char ln5[] = "this is a test";
    inCmmts = 1;
    rmvCmmts(ln5, &inCmmts);
    mu_assert(strcmp(ln5, "") == 0, "ln5 is not \'\'");
    mu_assert(inCmmts == 1, "inCmmts is not reset to 0");

    return NULL;
}

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
    mu_run_test(test_rmvCmmts);

    return NULL;
}

RUN_TESTS(all_tests);
