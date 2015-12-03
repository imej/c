/* test errno macro */
#include "lr/assert.h"
#include "errno.h"
#include <math.h>
#include <stdio.h>

int main() 
{
    assert_r(errno == 0);
    perror("No error reported as");

    errno = ERANGE;
    assert_r(errno == ERANGE);
    perror("Range error reported as");

    errno = 0;
    assert_r(errno == 0);

    sqrt(-1.0);
    assert_r(errno == EDOM);
    perror("Domain error reported as");
    puts("SUCCESS testing <errno.h>");
    return 0;
}
