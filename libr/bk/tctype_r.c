/* test ctype functions and macros */
#include "assert_r.h"
#include "ctype_r.h"
#include <limits.h>
#include <stdio.h>

static void prclass(const char *name, int (*fn)(int))
{
    // display a printable character class
    int c;

    fputs(name, stdout);
    fputs(": ", stdout);

    for (c = EOF; c <= UCHAR_MAX; ++c) {
        if ((*fn)(c)) {
	    fputc(c, stdout);
	}
    }

    fputs("\n", stdout);
}

int main()
{
    // test both macros and functions
    char *s;
    int c;

    // display printable classes
    prclass("ispunct", ispunct);

    if (ispunct(2300)) {
        fputs("work for 2300\n", stdout);
    } else {
        fputs("still work for 2300\n", stdout);
    }

    return 0;
}
