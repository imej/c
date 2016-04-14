/* exercise 5-4 strend(s, t) returns 1 if t occurs at the end of s, and zero otherwise. */
#include <stdio.h>

int strend(char *s, char *t);

int main(void) 
{
    char s[] = "Hello";
    char t[] = "Hello ";

    printf("strend(\"%s\", \"%s\") = %d\n", s, t, strend(s, t));

    return 0;
}

int strend(char *s, char *t)
{
    int ls = 0;
    int lt = 0;
    int i;

    while (*s != '\0') {
        s++;
	ls++;
    }

    while (*t != '\0') {
        t++;
	lt++;
    }

    if (lt > ls) {
        return 0;
    }

    for (i = 0; i <= lt; i++) {
        if (*(s--) != *(t--)) {
	    return 0;
	}
    }

    return 1;
}
