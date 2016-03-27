/* Exercise 2-7. function invert(x, p, n) that returns x with the n bits that 
   begin at position p inverted. */
#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(void)
{
    unsigned x = 0;

    printf("%u\n", invert(x, 1, 2));

    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    int sz = sizeof(unsigned) * 8;
    unsigned m = (((unsigned)~0) >> (sz - p -1)) & (~0 << (p - n + 1));
    return x ^ m;
}
