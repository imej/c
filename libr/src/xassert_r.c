#include <stdio.h>    // fputs
#include <stdlib.h>   // abort
#include "assert_r.h"

void _Assert_r(char *msg)
{
    fputs(msg, stderr);
    fputs(" -- assertion failed\n", stderr);
    abort();
}

