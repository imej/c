/* exercise 2-8: rightrot(x, n) - a function that returns the value of the integer
   x rotated to the right by n bit positions. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rightrot(int x, int n);
int i2bs(int x, char str[]);

int main(void)
{
    int i = 7;
    char str[32] = "                                ";
    i2bs(rightrot(i, 4), str);
    printf("%s\n", str);
    return 0;
}

int rightrot(int x, int n)
{
    int sz = sizeof(int) * 8;
    int rr = x & ~(~0 << n);
    rr = rr << (sz - n);
    x = x >> n;
    int left = ((unsigned)~0) >> n;
    return (left & x) | rr; 
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
