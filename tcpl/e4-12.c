/* exercise 4-12: recursive version of itoa */
#include <string.h>
#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[]);
void cia(int n, char s[]);
int sp;

int main(void) 
{
    char s[33] = {0};
    int i = 2345;
    int j = -8790;
    itoa(i, s);
    printf("%s\n", s);
    itoa(j, s);
    printf("%s\n", s);

    return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    sp = 0;
    cia(n, s);
    s[sp] = '\0';
}

void cia(int n, char s[])
{
    if (n < 0) {
        s[sp++] = '-';
	n = -n;
    }

    if (n / 10) {
        cia(n / 10, s);
    }

    s[sp++] = '0' + n % 10;
}
