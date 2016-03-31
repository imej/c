/* exercise 2-9: x &= (x-1) delete the rightmost 1-bit in x. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i2bs(int x, char str[]);

int main(void)
{
    char str[32] = "                                ";
    int i = 4;
    i2bs(i, str);
    printf("%s\n", str);

    i &= (i-1);
    i2bs(i, str);
    printf("%s\n", str);

    return 0;
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
