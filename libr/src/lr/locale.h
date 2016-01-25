/* locale.h standard header */
#ifndef _LOCALE_
#define _LOCALE_
#ifndef _YVALS_
#include "lr/yvals.h"
#endif

/* macros */
#define NULL _NULL

/* locale codes */
#define LC_ALL         0
#define LC_COLLATE     1
#define LC_CTYPE       2
#define LC_MONETARY    3
#define LC_NUMERIC     4
#define LC_TIME        5
/* ADD YOURS HERE */

#define _NCAT          6

/* type definitions */
struct lconv {
    /* controlled by LC_NUMERIC */
    char *decimal_point;
    char *thousands_sep;
    char *grouping;

    /* controlled by LC_MONETARY */
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;

};

/* declarations */
struct lconv *localeconv(void);
char *setlocale(int, const char *);
extern struct lconv _Locale;

/* macro overrides */
#define localeconv() (&_Locale)
#endif
