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
    mu_assert(strcmp((const char *)bstr1->data, "how are you?how old are you?") == 0, "test_bconcat: bconcat not concatenated.");

    return NULL;
}

char * test_bstricmp()
{
    char *p1 = "how are you?";
    bstring bstr1 = bfromcstr(p1);
    mu_assert(bstr1 != NULL, "test_bstricmp: bstring was not created via bfromcstr.");

    char *p2 = "how old are you?";
    bstring bstr2 = bfromcstr(p2);
    mu_assert(bstr2 != NULL, "test_bstricmp: bstring was not created via bfromcstr.");

    int rc = bstricmp(bstr1, bstr2);
    mu_assert(rc != BSTR_OK, "test_bstricmp: bconcat failed.");

    bassigncstr(bstr2, "how are you?");
    rc = bstricmp(bstr1, bstr2);
    mu_assert(rc == BSTR_OK, "test_bstricmp: bconcat failed.");

    return NULL;
}


char * test_biseq()
{
    char *p1 = "how are you?";
    bstring bstr1 = bfromcstr(p1);
    mu_assert(bstr1 != NULL, "test_biseq: bstring was not created via bfromcstr.");

    char *p2 = "how old are you?";
    bstring bstr2 = bfromcstr(p2);
    mu_assert(bstr2 != NULL, "test_biseq: bstring was not created via bfromcstr.");

    int rc = biseq(bstr1, bstr2);
    mu_assert(rc == 0, "test_biseq: biseq failed.");

    bassigncstr(bstr2, "how are you?");
    rc = biseq(bstr1, bstr2);
    mu_assert(rc == 1, "test_biseq: biseq failed.");

    return NULL;
}


char * test_binstr()
{
    char *p1 = "how are you?";
    bstring bstr1 = bfromcstr(p1);
    mu_assert(bstr1 != NULL, "test_binstr: bstring was not created via bfromcstr.");

    char *p2 = "how old are you?";
    bstring bstr2 = bfromcstr(p2);
    mu_assert(bstr2 != NULL, "test_binstr: bstring was not created via bfromcstr.");

    int rc = binstr(bstr1,0, bstr2);
    mu_assert(rc < 0, "test_binstr: binstr failed.");

    bassigncstr(bstr2, "are");
    rc = binstr(bstr1, 0, bstr2);
    mu_assert(rc == 4, "test_binstr: binstr failed.");

    return NULL;
}

char * test_bfindreplace()
{
    char *p1 = "how are you?";
    bstring bstr1 = bfromcstr(p1);
    mu_assert(bstr1 != NULL, "test_bfindreplace: bstring was not created via bfromcstr.");

    char *p2 = "you";
    bstring bstr2 = bfromcstr(p2);
    mu_assert(bstr2 != NULL, "test_bfindreplace: bstring was not created via bfromcstr.");

    char *p3 = "they";
    bstring bstr3 = bfromcstr(p3);
    mu_assert(bstr3 != NULL, "test_bfindreplace: bstring was not created via bfromcstr.");

    int rc = bfindreplace(bstr1, bstr2, bstr3, 0);
    mu_assert(rc == 0, "test_bfindreplace: binstr failed.");
    mu_assert(binstr(bstr1, 0, bstr3) > 0, "test_bfindreplace: binstr failed.");
    mu_assert(binstr(bstr1, 0, bstr2) < 0, "test_bfindreplace: binstr failed.");

    return NULL;
}

char * test_bsplit()
{
    char *p1 = "how are you?";
    bstring bstr1 = bfromcstr(p1);
    mu_assert(bstr1 != NULL, "test_bfindreplace: bstring was not created via bfromcstr.");

    struct bstrList *  blst = bsplit(bstr1, ' ');
    mu_assert(blst != NULL, "test_bsplit: bsplit failed.");
    mu_assert(blst->qty == 3, "test_bsplit: bsplit failed.");
    mu_assert(biseq(blst->entry[0], bfromcstr("how")), "test_bsplit: bsplit failed.");
    mu_assert(biseq(blst->entry[1], bfromcstr("are")), "test_bsplit: bsplit failed.");
    mu_assert(biseq(blst->entry[2], bfromcstr("you?")), "test_bsplit: bsplit failed.");
        
    return NULL;
}


char * test_bformat()
{
    char * chp = "Good!";
    bstring bstr1 = bformat("How are you? %s", chp);
    mu_assert(bstr1 != NULL, "test_bformat: bstring was not created via bformat.");
    mu_assert(biseq(bstr1, bfromcstr("How are you? Good!")), "test_bformat: bformat failed.");
        
    return NULL;
}

char * test_blength()
{
    bstring bstr1 = bfromcstr("How are you");
    mu_assert(bstr1 != NULL, "test_blength: bstring was not created via bfromcstr.");

    int rc = blength(bstr1);
    mu_assert(rc == 11, "test_blength: bformat failed.");
        
    return NULL;
}

char * test_bdata()
{
    bstring bstr1 = bfromcstr("How are you");
    mu_assert(bstr1 != NULL, "test_bdata: bstring was not created via bfromcstr.");

    char * ch = bdata(bstr1);
    mu_assert(strcmp(ch, "How are you") == 0, "test_bdata: bdata failed.");
        
    return NULL;
}

char * test_bchar()
{
    bstring bstr1 = bfromcstr("How are you");
    mu_assert(bstr1 != NULL, "test_bchar: bstring was not created via bfromcstr.");

    char ch = bchar(bstr1, 2);
    mu_assert(ch == 'w', "test_bchar: bchar failed.");
        
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
    mu_run_test(test_bstricmp);
    mu_run_test(test_biseq);
    mu_run_test(test_binstr);
    mu_run_test(test_bfindreplace);
    mu_run_test(test_bsplit);
    mu_run_test(test_bformat);
    mu_run_test(test_blength);
    mu_run_test(test_bdata);
    mu_run_test(test_bchar);

    return NULL;
}

RUN_TESTS(all_tests);
