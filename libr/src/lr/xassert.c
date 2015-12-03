#include <stdio.h>    // fputs
#include <stdlib.h>   // abort
#include "lr/assert.h"

void _Assert(char *msg)
{
    fputs(msg, stderr);
    fputs(" -- assertion failed\n", stderr);
    abort();
}

