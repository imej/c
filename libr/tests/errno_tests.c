/* test ctype functions and macros */
#include "lr/errno.h"
#include <math.h>
#include <stdio.h>
#define my_assert(test, message) if (!(test)) { fprintf(stderr, "[ERROR] (%s:%d: errno: %d) " message "\n", __FILE__, __LINE__, errno_r);}

int main()
{
    my_assert(errno_r == 0, "errno should be zero.");

    errno_r = ERANGE;
    my_assert(errno_r == ERANGE, "errno should be ERANGE");

    errno_r = 0;
    my_assert(errno_r == 0, "errno should be zero.");

    sqrt(-1.0);
    my_assert(errno_r == EDOM, "sqrt(-1.0) should return a domain error.");

    return 0;
}
