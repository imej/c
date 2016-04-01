/* exercise 3-4 */
#include <string.h>
#include <stdio.h>
#include <limits.h>

void reverse(char s[]);
void itoa(int n, char s[]);
void aitoa(int n, char s[]);

int main(void) 
{
    char s[33] = {0};
    int i = 2345;
    int j = -8790;
    aitoa(i, s);
    printf("%s\n", s);
    aitoa(j, s);
    printf("%s\n", s);
    aitoa(INT_MIN, s);
    printf("%s\n", s);
    itoa(INT_MIN, s);
    printf("%s\n", s);

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

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

/* aitoa: another itoa that handles the largest negative */
void aitoa(int n, char s[])
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

    s[i] = '\0';
    reverse(s);
}
