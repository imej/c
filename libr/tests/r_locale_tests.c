/* test standard locale.h */
#include "lr/locale.h"
#include <stdio.h>
#include "minunit.h"

char *test_localeconv()
{
    struct lconv *p = localeconv();

    mu_assert(p != NULL, "localeconv returns NULL.");

    printf("decimal_point: %s\n",p->decimal_point);
    printf("thousands_sep: %s\n",p->thousands_sep);
    printf("grouping: %s\n",p->grouping);
    printf("int_curr_symbol: %s\n",p->int_curr_symbol);
    printf("currency_symbol: %s\n",p->currency_symbol);
    printf("mon_decimal_point: %s\n",p->mon_decimal_point);
    printf("mon_thousands_sep: %s\n",p->mon_thousands_sep);
    printf("mon_grouping: %s\n",p->mon_grouping);
    printf("positive_sign: %s\n",p->positive_sign);
    printf("negative_sign: %s\n",p->negative_sign);
    printf("int_frac_digits: %d\n",p->int_frac_digits);
    printf("frac_digits: %d\n",p->frac_digits);
    printf("p_cs_precedes: %d\n",p->p_cs_precedes);
    printf("p_sep_by_space: %d\n",p->p_sep_by_space);
    printf("n_cs_precedes: %d\n",p->n_cs_precedes);
    printf("n_sep_by_space: %d\n",p->n_sep_by_space);
    printf("p_sign_posn: %d\n",p->p_sign_posn);
    printf("n_sign_posn: %d\n",p->n_sign_posn);

    return NULL;
}

char *test_setlocale()
{

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_localeconv);
    // mu_run_test(test_setlocale);
    
    return NULL;
}

RUN_TESTS(all_tests)
