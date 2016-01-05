/* test limists macros */
#include "lr/limits.h"
#include <stdio.h>
#include "minunit.h"

void print_macros()
{
    printf("CHAR_BIT = %2i   MB_LEN_MAX = %2i\n\n", CHAR_BIT, MB_LEN_MAX);
    printf("CHAR_MAX = %10i  CHAR_MIN = %10i\n", CHAR_MAX, CHAR_MIN);
    printf("SCHAR_MAX = %10i   SCHAR_MIN = %10i\n", SCHAR_MAX, SCHAR_MIN);
    printf("UCHAR_MAX = %10u\n", UCHAR_MAX);
    printf("SHRT_MAX = %10i   SHRT_MIN = %10i\n", SHRT_MAX, SHRT_MIN);
    printf("USHRT_MAX = %10U\n\n", USHRT_MAX);
    printf("INT_MAX = %10i   INT_MIN = %10i\n", INT_MAX, INT_MIN);
    printf("UINT_MAX = %10u\n\n", UINT_MAX);
    printf("LONG_MAX = %10li   LONG_MIN = %10li\n", LONG_MAX, LONG_MIN);
    printf("ULONG_MAX = %10lu\n", ULONG_MAX);
}

char *test_char()
{
    mu_assert(!(CHAR_BIT < 8 || CHAR_MAX < 127 || 0 < CHAR_MIN || CHAR_MAX != SCHAR_MAX && CHAR_MAX != UCHAR_MAX), "Bad char properties");
    return NULL;
}

char *test_int()
{
    mu_assert(!(INT_MAX < 32767 || -32767 < INT_MIN || INT_MAX < SHRT_MAX), "Bad int properties");
    return NULL;
}

char *test_long()
{
    mu_assert(!(LONG_MAX < 2147483647 || -2147483647 < LONG_MIN || LONG_MAX < INT_MAX), "Bad long properties");
    return NULL;
}

char *test_mb_len_max()
{
    mu_assert(MB_LEN_MAX > 0, "Bad MB_LEN_MAX");
    return NULL;
}

char *test_signed_char()
{
    mu_assert(SCHAR_MAX >= 127 && -127 >= SCHAR_MIN, "Bad signed char properties")
    return NULL;
}

char *test_short()
{
    mu_assert(SHRT_MAX >= 32767 && -32767 >= SHRT_MIN && SHRT_MAX < SCHAR_MAX, "Bad signed short properties")
    return NULL;
}

char *test_unsigned_char()
{
    mu_assert(UCHAR_MAX >= 255 && UCHAR_MAX / 2 >= SCHAR_MAX, "Bad unsigned char properties")
    return NULL;
}

char *test_unsigned_int()
{
    mu_assert(UINT_MAX >= 65535 && UINT_MAX / 2 >= INT_MAX && UINT_MAX >= USHRT_MAX, "Bad unsigned int properties")
    return NULL;
}

char *test_unsigned_long()
{
    mu_assert(ULONG_MAX >= 4294967295 && ULONG_MAX / 2 >= LONG_MAX && ULONG_MAX >= UINT_MAX, "Bad unsigned long properties")
    return NULL;
}

char *test_unsigned_short()
{
    mu_assert(USHRT_MAX >= 65535 && USHRT_MAX / 2 >= SHRT_MAX && USHRT_MAX >= UCHAR_MAX, "Bad unsigned short properties")
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_char);
    mu_run_test(test_int);
    mu_run_test(test_long);
    mu_run_test(test_mb_len_max);
    mu_run_test(test_signed_char);
    mu_run_test(test_short);
    mu_run_test(test_unsigned_char);
    mu_run_test(test_unsigned_int);
    mu_run_test(test_unsigned_long);
    mu_run_test(test_unsigned_short);
    
    return NULL;
}
