/**
 * Test assert_r macro 
 */
#ifndef NDEBUG
    #define NDEBUG
#endif
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "assert_r.h"

/* staic data */
static int val = 0;

static void field_abort(int sig)
{
    /* handle SIGABRT */
    if (val == 1){ /* expected result */
        puts("SUCCESS testing <assert_r.h>");
        exit(EXIT_SUCCESS);
    } else { /*unexpected result */
        puts("FAILURE testing <assert_r.h>");
        exit(EXIT_FAILURE);
    } 
}

static void dummy()
{
    /* test dummy assert_r macro */
    int i = 0;

    assert_r(i == 0);
    assert_r(i == 1);
}

#ifdef NDEBUG
    #undef NDEBUG
#endif
#include "assert_r.h"

int main()
{
    /* test both dummy and working forms */
    assert_r(signal(SIGABRT, &field_abort) != SIG_ERR);
    dummy();    /* should not abort */

    assert_r(val == 0);
    ++val;
    fputs("Sample assert_rion failure message --\n", stderr);
    assert_r(val == 0);
    puts("FAILURE testing <assert_r.h>");
    return (EXIT_FAILURE);
}
