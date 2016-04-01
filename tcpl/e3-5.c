/* exercise 3-5 */
#include <string.h>
#include <stdio.h>
#include <limits.h>

void reverse(char s[]);
void itob(int n, char s[], int b);

int main(void) 
{
    char s[33] = {0};
    int i = 2345;
    int j = -8790;
    itob(i, s, 16);
    printf("%s\n", s);
    itob(j, s, 16);
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

/* itob: converts the integer n into a base b character representation in the string s */
void itob(int n, char s[], int b)
{
    int i, sign;

    if (n < 0) {
        sign = -1;
    } else {
        sign = 1;
    }

    i = 0;
    do {
        s[i++] = (n % b) * sign + '0';
    } while ((n /= b) * sign > 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}
