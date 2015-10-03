#include <stdio.h>
#include <string.h>
#include <lcthw/bstrlib.h>
#include "minunit.h"
#include <assert.h>

char * test_bfromcstr()
{
    char *str = "how are you?";
    bstring bstr = bfromcstr(str);

    mu_assert(bstr != NULL, "bstring was not created via bfromcstr.");
    mu_assert(strcmp(str, (const char *)bstr->data) == 0, "bstring is different from the string");

    return NULL;
}

char * test_blk2bstr()
{
    void *p = "how are you?";
    bstring bstr = blk2bstr(p, 6);

    mu_assert(bstr != NULL, "bstring was not created via blk2bstr.");
    mu_assert(strcmp("how ar", (const char *)bstr->data) == 0, "bstring is different from the string");

    return NULL;
}

char * test_bstrcpy()
{
    char *p = "how are you?";
    bstring bstr = bfromcstr(p);
    mu_assert(bstr != NULL, "test_bstrcpy: bstring was not created via bfromcstr.");

    bstring bstr2 = bstrcpy(bstr);
    mu_assert(bstr2 != NULL, "test_bstrcpy: bstring was not created via bstrcpy.");
    mu_assert(strcmp((const char *)bstr2->data, (const char *)bstr->data) == 0, "bstring is not copied properly");

    return NULL;
}

char * test_bassign()
{
    char *p1 = "how are you?";
    char *p2 = "I am fine. Thanks!";

    bstring bstr1 = bfromcstr(p1);
    mu_assert(bstr1 != NULL, "test_bassign: bstring was not created via bfromcstr.");
    mu_assert(strcmp((const char *)bstr1->data, p1) == 0, "bstring is not created properly");

    bstring bstr2 = bfromcstr(p2);
    mu_assert(bstr2 != NULL, "test_bassign: bstring was not created via bfromcstr.");
    mu_assert(strcmp((const char *)bstr2->data, p2) == 0, "bstring is not created properly");

    int rc = bassign(bstr1, bstr2);
    mu_assert(rc == BSTR_OK, "test_bassign: bassign failed.");
    mu_assert(strcmp((const char *)bstr2->data, (const char *)bstr1->data) == 0 && bstr1->mlen == bstr2->mlen && bstr1->slen == bstr2->slen, "bstring is not assigned properly");

    return NULL;
}

char * test_bassigncstr()
{
    char *p = "how are you?";
    bstring bstr = bfromcstr(p);
    mu_assert(bstr != NULL, "test_bassigncstr: bstring was not created via bfromcstr.");

    char *p1 = "good";
    int rc = bassigncstr(bstr, p1);
    mu_assert(rc == BSTR_OK, "test_bassigncstr: bassigncstr failed.");
    mu_assert(bstr != NULL, "test_bassigncstr: bstring was set to NULL by bassigncstr.");
    mu_assert(strcmp((const char *)bstr->data, p1) == 0, "bstring is not assigned from cstr properly");

    return NULL;
}

char * test_bassignblk()
{
    char *p = "how are you?";
    bstring bstr = bfromcstr(p);
    mu_assert(bstr != NULL, "test_bassignblk: bstring was not created via bfromcstr.");

    char *p1 = "good bye";
    int rc = bassignblk(bstr, p1, 6);
    mu_assert(rc == BSTR_OK, "test_bassignblk: bassignblk failed.");
    mu_assert(bstr != NULL, "test_bassignblk: bstring was set to NULL by bassignblk.");
    mu_assert(strcmp((const char *)bstr->data, "good b") == 0, "test_bassignblk: bstring is not assigned from cstr properly");

    return NULL;
}

char * test_bdestroy()
{
    char *p = "how are you?";
    bstring bstr = bfromcstr(p);
    mu_assert(bstr != NULL, "test_bdestroy: bstring was not created via bfromcstr.");

    int rc = bdestroy(bstr);
    mu_assert(rc == BSTR_OK, "test_bdestroy: bdestroy failed.");

    return NULL;
}

char * test_bconcat()
{
    char *p1 = "how are you?";
    bstring bstr1 = bfromcstr(p1);
    mu_assert(bstr1 != NULL, "test_bconcat: bstring was not created via bfromcstr.");

    char *p2 = "how old are you?";
    bstring bstr2 = bfromcstr(p2);
    mu_assert(bstr2 != NULL, "test_bconcat: bstring was not created via bfromcstr.");

    int rc = bconcat(bstr1, bstr2);
    mu_assert(rc == BSTR_OK, "test_bconcat: bconcat failed.");
    mu_assert(strcmp((const char *)bstr1->data, "how are you?how old are you?" == BSTR_OK, "test_bconcat: bconcat not concatenated.");

    return NULL;
}

char * all_tests()
{
    mu_suite_start();

    mu_run_test(test_bfromcstr);
    mu_run_test(test_blk2bstr);
    mu_run_test(test_bstrcpy);
    mu_run_test(test_bassign);
    mu_run_test(test_bassigncstr);
    mu_run_test(test_bassignblk);
    mu_run_test(test_bdestroy);
    mu_run_test(test_bconcat);

    return NULL;
}

RUN_TESTS(all_tests);
