/* Exercise 6-3: This file contains functions to read the input. */
#include "header.h"

int catchline(char s[], int lim)
{
    int c, i;

    for (i = 0, c = 0; i < lim - 1 && (c = getchar()) != EOF && c!= '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
	++i;
    }

    s[i] = '\0';
    return i;
}
