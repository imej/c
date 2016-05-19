#include "minunit.h"
#include <header.h>
#include <assert.h>

char * test_isPrepro()
{
    char ln1[] = "this is a test.";
    int inpp = 0;
    mu_assert(isPrepro(ln1, &inpp) == 0, "'this is a test.' is a macro");

    char ln2[] = "#this is a test.";
    inpp = 0;
    mu_assert(isPrepro(ln2, &inpp) == 1, "'#this is a test.' is not a macro");

    char ln3[] = "#this is a test.\\";
    inpp = 0;
    mu_assert(isPrepro(ln3, &inpp) == 1, "'#this is a test.\\ \' is not a macro");
    mu_assert(inpp == 1, "'#this is a test.\\ \' followed by a macro");

    char ln4[] = "this is a test.";
    inpp = 1;
    mu_assert(isPrepro(ln4, &inpp) == 1, "'this is a test.' is a macro when it is within a macro");
    mu_assert(inpp == 0, "'this is a test.' is not followed by a macro");


    return NULL;
}
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

    /* treeprint(root); */
    tdestroy(root);

    return NULL;
}

char *test_fromSortedArray()
{
    char *sa[] = {"aaa", "bbb", "ccc", "ddd", "eee"};

    struct tnode *tree = fromSortedArray(sa, 0, 4);

    mu_assert(strcmp(tree->word, sa[2]) == 0, "'ccc' is not root.");
    mu_assert(strcmp(tree->left->word, sa[0]) == 0, "'aaa' is not the first left.");
    mu_assert(strcmp(tree->right->word, sa[3]) == 0, "'ddd' is not the first left.");
    mu_assert(strcmp(tree->left->right->word, sa[1]) == 0, "'bbb' is not the first left.");
    mu_assert(strcmp(tree->right->right->word, sa[4]) == 0, "'eee' is not the first left.");

    mu_assert(intree(tree, sa[2]) == 1, "'ccc' is not in the tree.");
    mu_assert(intree(tree, sa[1]) == 1, "'bbb' is not in the tree.");
    mu_assert(intree(tree, "zzz") == 0, "'zzz' is in the tree.");

    /* treeprint(tree); */

    tdestroy(tree);

    return NULL;
}

char *test_ckeys()
{
    struct tnode *tree = createKeyTree();
    treeprint(tree);
    tdestroy(tree);

    return NULL;
}

char *test_getvar()
{
    char line[] = "how are you?";
    char rv[MAXLINE] = {0};
    struct tnode *tree = createKeyTree();
    int i = 0;
     
    i = getvar(line, i, tree, rv);
    
    mu_assert(i == 3, "the first word should be ended at position 3");
    mu_assert(strcmp(rv,"how") == 0, "the first word is not 'how'");

    i = getvar(line, i, tree, rv);
    
    mu_assert(i == 7, "the second word should be ended at position 7");
    mu_assert(strcmp(rv,"are") == 0, "the second word is not 'are'");
    
    i = getvar(line, i, tree, rv);
    
    mu_assert(i == 11, "the second word should be ended at position 11");
    mu_assert(strcmp(rv,"you") == 0, "the third word is not 'you'");
    
    i = getvar(line, i, tree, rv);
    
    mu_assert(i == -1,"the fourth word does not exist");
    
    tdestroy(tree);

    return NULL;
}

char *test_prtgrp()
{
    char *sa[] = {"aaaa", "aaab", "aaac", "aabd", "aabe"};
    struct tnode *tree = fromSortedArray(sa, 0, 4);
    char grp[MAXLINE] = {0};

    prtgrp(tree, 3, grp);

    tdestroy(tree);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_tree);
    mu_run_test(test_rmvCmmts);
    mu_run_test(test_isPrepro);
    mu_run_test(test_fromSortedArray);
    /* mu_run_test(test_ckeys); */
    mu_run_test(test_getvar);
    mu_run_test(test_prtgrp);

    return NULL;
}

RUN_TESTS(all_tests);
