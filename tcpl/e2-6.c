/* Exercise 2-6 funciton setbits(x, p, n, y) that returns x with the n
   bits that begin at position p set to the rightmost n bit of y, leaving
   the other bits unchanged. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned getbits(unsigned x, int p, int n);
int i2bs(int x, char str[]);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void)
{
    char str[33] = "                                 ";
    unsigned int x = 120;
    unsigned int y = 12;

    i2bs(setbits(x, 4, 3, y), str);

    printf("%s\n", str);

    return 0;
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

/* populate the passed in string with the binary sequence of the passed in int */
int i2bs(int x, char str[])
{
    int size, i, tmp;
    char c;
    size = sizeof(int) * 8;
    
    if (str == NULL) {
        return -1;
    }

    if (strlen(str) < size) {
        str = realloc(str, size+1);
    }

    for (i = 0; i < size; i++) {
        tmp = x & ((unsigned)(1 << (size-1)) >> i);
	c = tmp > 0 ? '1' : '0';
	str[i] = c;
    }

    str[i] = '\0';

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    /*
    int size;
    size = sizeof(unsigned int) * 8;
    */
    char str[33] = "                                 ";
    i2bs(x, str);
    printf("x = %s\n", str);
    i2bs(y, str);
    printf("y = %s\n", str);
    
    unsigned left = x >> (p + 1) << (p + 1);
    i2bs(left, str);
    printf("l = %s\n", str);

    unsigned right = x & ~(~0 << (p + 1 - n));
    i2bs(right, str);
    printf("r = %s\n", str);

    unsigned middle = (y & ~(~0 << n)) << (p + 1 - n);
    i2bs(middle, str);
    printf("m = %s\n", str);

    return left | middle | right;   
}
