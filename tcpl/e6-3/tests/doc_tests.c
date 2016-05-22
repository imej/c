#include "minunit.h"
#include <header.h>
#include <assert.h>

char *test_getword()
{
    char line[] = "how are you?";
    char rv[MAXLINE] = {0};
    struct tnode *tree = createKeyTree();
    int i = 0;
     
    i = getword(line, i, tree, rv);
    
    mu_assert(i == 3, "the first word should be ended at position 3");
    mu_assert(strcmp(rv,"how") == 0, "the first word is not 'how'");

    i = getword(line, i, tree, rv);
    
    mu_assert(i == 7, "the second word should be ended at position 7");
    mu_assert(strcmp(rv,"are") == 0, "the second word is not 'are'");
    
    i = getword(line, i, tree, rv);
    
    mu_assert(i == 11, "the second word should be ended at position 11");
    mu_assert(strcmp(rv,"you") == 0, "the third word is not 'you'");
    
    i = getword(line, i, tree, rv);
    
    mu_assert(i == -1,"the fourth word does not exist");
    
    tdestroy(tree);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_getword);

    return NULL;
}

RUN_TESTS(all_tests);
