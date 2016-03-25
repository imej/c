/* Exercise 2-6 funciton setbits(x, p, n, y) that returns x with the n
   bits that begin at position p set to the rightmost n bit of y, leaving
   the other bits unchanged. */
#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main(void)
{
    printf("%d\n", getbits(2, 1, 1));
    return 0;
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}
