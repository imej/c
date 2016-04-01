/* exercise 3-6 */
#include <string.h>
#include <stdio.h>
#include <limits.h>

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main(void) 
{
    char s[33] = {0};
    int i = 2345;
    itoa(i, s, 8);
    printf("|%s|\n", s);

    return 0;
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
	s[i] = s[j];
	s[j] = c;
    }
}

/* itoa: minimum field width version. */
void itoa(int n, char s[], int w)
{
    int i, sign;

    if (n < 0) {
        sign = -1;
    } else {
        sign = 1;
    }

    i = 0;
    do {
        s[i++] = (n % 10) * sign + '0';
    } while ((n /= 10) * sign > 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    while (i < w + 1) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}
